from cs50 import get_string


def main():
    number = get_string('Number: ')
    if not is_valid(number):
        print('INVALID')
    elif is_visa(number):
        print('VISA')
    elif is_mastercard(number):
        print('MASTERCARD')
    elif is_american_express(number):
        print('AMEX')
    else:
        print('INVALID')


def is_valid(number):
    digits = ''
    for i in range(len(number) - 2, -1, -2):
        double = int(number[i]) * 2
        digits += str(double)
    
    for i in range(len(number) - 1, -1, -2):
        digits += number[i]
    
    total_sum = sum([int(digit) for digit in list(digits)])
    return total_sum % 10 == 0


def is_visa(number):
    if (len(number) not in [13, 16]):
        return False
    
    return number[0] == "4"


def is_mastercard(number):
    if (len(number) != 16):
        return False
    
    return int(number[0:2]) in range(51, 56)


def is_american_express(number):
    if (len(number) != 15):
        return False

    return number[0:2] in ['34', '37']


main()
