from cs50 import get_int

sum_of_evens = 0
sum_of_odd = 0
digits = 0
number = 0
number2 = 0

while True:
    card = get_int("Number: ")
    if card > 0:
        break

while card > 0:
    digits += 1
    number2 = number
    number = card % 10

    if digits % 2 == 0:
        multiply = number * 2
        sum_of_evens += (multiply // 10) + (multiply % 10)
    else:
        sum_of_odd += number
    card = card // 10

firstn = number * 10 + number2

# card validity checker
if (sum_of_evens + sum_of_odd) % 10 == 0:

    if (digits == 13 or digits == 16) and number == 4:
        print("VISA")
    elif digits == 15 and (firstn == 34 or firstn == 37):
        print("AMEX")
    elif digits == 16 and firstn >= 51 and firstn <= 55:
        print("MASTERCARD")
    else:
        print("INVALID")

else:
    print("INVALID")