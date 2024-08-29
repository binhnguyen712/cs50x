from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break
change = change * 100
total_quarters = change // 25
change -= total_quarters*25

total_dimes = change // 10
change -= total_dimes*10

total_nickles = change // 5
change -= total_nickles*5

total_pennies = change // 1

print(int(total_quarters + total_dimes + total_nickles + total_pennies))

