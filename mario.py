while True:
    n = int(input("Height: "))
    if type(n)!=="int":
        print("Please enter integer value")
        break
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