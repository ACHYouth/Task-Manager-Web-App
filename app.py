from flask import Flask, render_template, request, redirect, url_for, session
import sqlite3
import os
import bcrypt
import hashlib
import secrets

app = Flask(__name__)
app.secret_key = os.urandom(24)

def create_table():
    conn = sqlite3.connect('tasks.db')
    c = conn.cursor()

    # Create the users table
    c.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            username TEXT NOT NULL UNIQUE,
            password_hash TEXT NOT NULL,
            salt TEXT NOT NULL
        )
    ''')

    # Create the tasks table
    c.execute('''
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY,
            user_id INTEGER NOT NULL,
            title TEXT NOT NULL,
            description TEXT,
            priority INTEGER,
            due_date DATE,
            completed INTEGER DEFAULT 0,
            FOREIGN KEY (user_id) REFERENCES users (id)
        )
    ''')

    conn.commit()
    conn.close()

# Helper function to get the user ID
def get_user_id(username):
    conn = sqlite3.connect('tasks.db')
    c = conn.cursor()
    c.execute('SELECT id FROM users WHERE username = ?', (username,))
    user_id = c.fetchone()[0]
    conn.close()
    return user_id

@app.route('/')
def index():
    if 'username' in session:
        username = session['username']
        user_id = get_user_id(username)

        conn = sqlite3.connect('tasks.db')
        c = conn.cursor()
        c.execute('SELECT * FROM tasks WHERE user_id = ? ORDER BY priority ASC, due_date ASC', (user_id,))
        tasks = c.fetchall()
        conn.close()

        return render_template('index.html', tasks=tasks)

    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    error_message = None

    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('tasks.db')
        c = conn.cursor()

        # Retrieve the salt for the given username
        c.execute('SELECT salt FROM users WHERE username = ?', (username,))
        salt = c.fetchone()

        if salt:
            salt = salt[0]
            # Hash the input password with the retrieved salt
            input_password_hash = hashlib.sha256((password + salt).encode()).hexdigest()

            # Retrieve the user with the matching username and hashed password
            c.execute('SELECT username FROM users WHERE username = ? AND password_hash = ?', (username, input_password_hash))
            user = c.fetchone()

            if user:
                session['username'] = user[0]
                conn.close()
                return redirect(url_for('index'))

        error_message = "Invalid username or password. Please try again."

    return render_template('login.html', error_message=error_message)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

@app.route('/add_task', methods=['GET', 'POST'])
def add_task():
    if request.method == 'POST':
        username = session['username']
        user_id = get_user_id(username)

        title = request.form['title']
        description = request.form['description']
        priority = int(request.form['priority'])
        due_date = request.form['due_date']

        conn = sqlite3.connect('tasks.db')
        c = conn.cursor()
        c.execute('INSERT INTO tasks (user_id, title, description, priority, due_date) VALUES (?, ?, ?, ?, ?)',
                  (user_id, title, description, priority, due_date))
        conn.commit()
        conn.close()

        return redirect(url_for('index'))

    return render_template('add_task.html')

@app.route('/mark_completed/<int:task_id>')
def mark_completed(task_id):
    conn = sqlite3.connect('tasks.db')
    c = conn.cursor()
    c.execute('UPDATE tasks SET completed = 1 WHERE id = ?', (task_id,))
    conn.commit()
    conn.close()
    return redirect(url_for('index'))


@app.route('/remove_task/<int:task_id>')
def remove_task(task_id):
    conn = sqlite3.connect('tasks.db')
    c = conn.cursor()
    c.execute('DELETE FROM tasks WHERE id = ?', (task_id,))
    conn.commit()
    conn.close()
    return redirect(url_for('index'))


@app.route('/view_task/<int:task_id>')
def view_task(task_id):
    conn = sqlite3.connect('tasks.db')
    c = conn.cursor()
    c.execute('SELECT * FROM tasks WHERE id = ?', (task_id,))
    task = c.fetchone()
    conn.close()

    if task:
        return render_template('view_task.html', task=task)
    else:
        return "Task not found"

def hash_password(password):
    salt = secrets.token_hex(8)
    password_hash = hashlib.sha256((password + salt).encode()).hexdigest()
    return password_hash, salt

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('tasks.db')
        c = conn.cursor()

        # Check if the username already exists in the database
        c.execute('SELECT id FROM users WHERE username = ?', (username,))
        existing_user = c.fetchone()

        if existing_user:
            error_message = "Username already exists. Please choose a different username."
            return render_template('register.html', error_message=error_message)

        # If the username is not taken, insert the new user into the database
        password_hash, salt = hash_password(password)
        c.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)', (username, password_hash, salt))
        conn.commit()
        conn.close()

        session['username'] = username
        return redirect(url_for('index'))

    return render_template('register.html')

@app.route('/delete_account', methods=['GET', 'POST'])
def delete_account():
    if 'username' in session:
        if request.method == 'POST':
            username = session['username']
            user_id = get_user_id(username)

            # Delete tasks associated with the user
            conn = sqlite3.connect('tasks.db')
            c = conn.cursor()
            c.execute('DELETE FROM tasks WHERE user_id = ?', (user_id,))
            conn.commit()

            # Delete the user account
            c.execute('DELETE FROM users WHERE id = ?', (user_id,))
            conn.commit()
            conn.close()

            # Logout the user and redirect to the login page
            session.pop('username', None)
            return redirect(url_for('login'))

        return render_template('delete_account.html')

    return redirect(url_for('login'))

@app.route('/undo_completed/<int:task_id>')
def undo_completed(task_id):
    conn = sqlite3.connect('tasks.db')
    c = conn.cursor()

    # Get the current completion status of the task
    c.execute('SELECT completed FROM tasks WHERE id = ?', (task_id,))
    current_status = c.fetchone()[0]

    # Toggle the completion status
    new_status = 0 if current_status == 1 else 1
    c.execute('UPDATE tasks SET completed = ? WHERE id = ?', (new_status, task_id))
    conn.commit()
    conn.close()

    return redirect(url_for('index'))

if __name__ == '__main__':
    create_table()
    app.run(debug=True)
