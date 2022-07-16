from cs50 import get_float

while (True):
    due = get_float("Change owed: ")
    if (due > 0):
        break

cents = due * 100

quarters = cents // 25
cents -= quarters * 25

dimes = cents // 10
cents -= dimes * 10

nickels = cents // 5
cents -= nickels * 5

pennies = cents
print(int(quarters + dimes + nickels + pennies))
