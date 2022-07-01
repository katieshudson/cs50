from cs50 import get_int

# variable for number of blocks
while True:
    num_blocks = get_int("How high should the pyramid be? ")
    if num_blocks > 0 and num_blocks < 9:
        break

# number of blocks must be between 0 and 9
for i in range(1, num_blocks + 1):
    spaces = num_blocks - i

    print(" " * spaces, end="")
    print("#" * i)