from cs50 import get_int

while (True):
    height = get_int("Height: ")
    if (height > 0 and height < 9):
        break

for i in range(1, height + 1):
    block = '#'
    space = ' '
    spacing = height - i
    print(f'{space * spacing}{block * i}{space}{block * i}')
