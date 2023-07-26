from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n >= 1 and n <= 8:
        break

for i in range(n):
    for j in range(n - 1, i - 1, -1):
        if j > i:
            print(" ", end="")
        if j == i:
            print("#", end="")
            print("#" * i, end="")

    print("  ", end="")

    for b in range(i + 1):
        print("#", end="")

    print()