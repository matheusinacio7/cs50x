from cs50 import get_string

def main():
    number = get_string("Number: ")
    print(check_if_valid(number))

def check_if_valid(number):
    digits = ''
    for i in range(len(number) - 2, -1, -2):
        double = int(number[i]) * 2
        digits += str(double)
    
    for i in range(len(number) - 1, -1, -2):
        digits += number[i]
    
    total_sum = sum([int(digit) for digit in list(digits)])
    return total_sum % 10 == 0

def check_if_visa(number):
    if (len(number) not in [13, 16]):
        return False

main()
