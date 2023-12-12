def main():
    Height = get_int()
    for i in range(Height):
        for k in range(i + 1, Height):
            print(" ", end="")
        for j in range(i + 1):
            print("#", end="")

        print("  ", end="")

        for j in range(i + 1):
            print("#", end="")
        print("", end="\n")


def get_int():
    while True:
        try:
            Height = int(input("Height: "))
            if 1 <= Height <= 8:
                return Height
        except ValueError:
            print("Not an integer")


main()
