val = 0b00010000

def b(a):
    print("{:08b}".format(a))

b(val)
b(val >> 4)

# 7 6 5 4 3 2 1 0
# 0 0 0 1 0 0 0 0
# 1 1 1 1 0 0 0 0