string = "Hello World"
num = input()
if eval(num) == 0:
    print("Hello World")
elif eval(num) > 0:
    i = 2
    while i < len(string) + 2:
        print(string[i-2:i], end='\n')
        i = i + 2
else:
    i = 0
    for i in range(len(string)):
        print(string[i], end='\n')
