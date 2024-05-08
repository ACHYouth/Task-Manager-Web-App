TASK MANAGER

Video Demo: https://youtu.be/-ktczVtPwRs

Description:
This is a web app I designed to help the user order their tasks based on the priority they assign to each task.
This web app has the following features:
1) User Authentication (Register, Login, Logout)
2) Add Tasks - You can give a name, description, priority level, and due date for each task
3) Tasks Menu - Shows the list of tasks you've added ordered by priority (highest priority task is at the top)
4) Mark Completed - To mark a task as complete.
5) Undo Completed - To mark a task as not complete
6) View Task - Clicking on the name of a task in the tasks menu brings you to its 'Task details' page which shows
                  you its name, description, priority level, due date, and status of completion.
7) Remove - This button removes a task
8) Delete Account - This button allows you to delete your account.

Keep in mind, you can create multiple accounts and hence this task manager can be used by multiple users. There is
also no upper limit on the number of tasks you can add (it depends on the storage capacity of your device.)

These are the files I used in this project:
1) style.css - This is a css file responsible for the design aspect of the web app.
2) add_task.html, delete_account.html, index.html, login.html, register.html, view_task.html - These are the html files responsible for the functioning of the 'add task', 'delete account', 'index' (homepage that contains the task menu), 'login', 'register', and 'view task' (task details) features of the web app respectively.
3) app.py - This is the core of the web app. This is the python file that is responsible for the working of the web app. It is responsible for creating and manipulating the SQL database and recieving and understanding user input, and contains routes to all the html files (various features of the app) mentioned in the previous point.
4) tasks.db - This is the database file that stores all the user data (the tasks of each user).


My journey with this project:

When I set out to create this application, my primary motivation was to streamline and simplify the task
management process for myself and others. As a person who values productivity and organization, I often found
myself struggling to keep track of various tasks and their priorities. I envisioned a tool that could effectively
help users like me order their tasks based on individual priority levels, ensuring that the most important ones
are always at the top of the list.

The project's potential applications in project management and personal organization excited me greatly. I
envisioned professionals, students, and busy individuals utilizing this app to efficiently manage their work,
studies, and daily activities. The idea of creating a platform that could positively impact people's lives by
reducing stress and boosting productivity fueled my passion for this project.

Regarding the design, initially, I wanted to make it vibrant and detailed, but ultimately, I opted for a
minimalistic and straightforward approach because I firmly believe that simplicity enhances user experience. I
wanted users to focus on their tasks rather than getting overwhelmed by a complex interface. By keeping the design
clean and intuitive, users would be able to navigate the app effortlessly, adding and prioritizing tasks without
unnecessary distractions.

As for the web app's uses, it caters to a wide range of needs. Students can utilize it to organize their
assignments and projects, while professionals can manage work-related tasks and deadlines effectively. The app's
ability to handle multiple accounts makes it suitable for teams or families to collaborate and coordinate tasks
efficiently. Additionally, the option to mark tasks as completed and undo them allows users to track their
progress and maintain clarity on ongoing activities.

Ultimately, my goal was to create a user-friendly, practical, and accessible task manager that anyone could
benefit from. I believe that by providing a tool that simplifies task organization and improves time management, I
could contribute to making people's lives more productive and stress-free. As I continue to refine and enhance the
web app, I hope to see it become a valuable asset in the lives of many users, supporting them in achieving their
goals and staying on top of their tasks with ease.
