temp = input()
if temp[0] == "C":
    num = (eval(temp[1:]) * 1.8) + 32
    print("F", end='')
    print("{:.2f}".format(num))
else:
    num = (eval(temp[1:]) - 32) / 1.8
    print("C", end='')
    print("{:.2f}".format(num))
