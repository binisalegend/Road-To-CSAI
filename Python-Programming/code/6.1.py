# Read in a dictionary type string, invert the key value pairs in the output

def invert_dict(d):
    return {v:k for k,v in d.items()}


str = eval(input())

try:
    print(invert_dict(str))
except:
    print("输入错误")