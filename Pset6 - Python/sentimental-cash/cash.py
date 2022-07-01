from cs50 import get_float


def main():

    # Ask how many cents the customer is owed
    while True:
        cents = get_float("Change owed: ")  # remaining cents
        if cents > -1:
            break

    # Calculate the number of quarters to give to the customer
    quarters = calculate_quarters(cents)
    cents = round(cents, 2)

    cents = (cents - (quarters * 0.25))
    cents = round(cents, 2)

    # Calculate the number of dimes to give to the customer
    dimes = calculate_dimes(cents)

    cents = (cents - (dimes * 0.10))
    cents = round(cents, 2)

    # Calculate the number of nickles to give to the customer
    nickles = calculate_nickles(cents)

    cents = (cents - (nickles * 0.05))
    cents = round(cents, 2)

    # Calculate the number of pennies to give to the customer
    pennies = calculate_pennies(cents)

    coins = quarters + dimes + nickles + pennies

    print(coins)


def calculate_quarters(cents):

    num_quarters = int(cents / 0.25)  # cents passed in here is a decimal, convert to int

    return num_quarters


def calculate_dimes(cents):

    num_dimes = int(cents / 0.10)  # cents passed in here is a decimal, convert to int

    return num_dimes


def calculate_nickles(cents):

    num_nickles = int(cents / 0.05)

    return num_nickles


def calculate_pennies(cents):

    num_pennies = int(cents/0.01)

    return num_pennies


if __name__ == "__main__":
    main()