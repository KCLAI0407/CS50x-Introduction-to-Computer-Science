def main():
    number = int(input("Number: "))
    # cal the checksum
    count = 0
    sum = 0
    digit = 0
    i = number
    while i > 0:
        digit = i % 10
        count += 1
        if count % 2 == 0:
            double_digit = 2 * digit
            if (double_digit // 10) != 0:
                sum += double_digit // 10
                sum += double_digit % 10
            else:
                sum += double_digit
        else:
            sum += digit
        i = i // 10

    if sum % 10 != 0:
        print("INVALID")
        return 1

    starting_digits = check_digit(number, count)
    if count == 15 and (starting_digits == 34 or starting_digits == 37):
        print("AMEX")
    elif count == 16 and (50 < starting_digits <= 55):
        print("MASTERCARD")
    elif (count == 13 or count == 16) and starting_digits == 4:
        print("VISA")
    else:
        print("INVALID")


def power(n, m):
    result = 1
    for i in range(m):
        result *= n
    return result


def check_digit(number, count):
    start = number // power(10, count - 1)
    if start == 4:
        return start
    else:
        start = number // power(10, count - 2)
    return start


main()
