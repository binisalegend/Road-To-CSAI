'''
Descripttion: 
version: 
Author: binisalegend
Date: 2023-10-22 21:22:54
LastEditors: binisalegend
LastEditTime: 2023-10-22 21:35:16
'''
a = input() 
length = len(a)
    
for i in range(length):
    if (a[i] >= '0' and a[i] <= '9') or a[i] == '.' or a[i] == '+' or a[i] == '-' or a[i] == 'j':
        continue
    else:
        print("输入有误")
        exit(0)

num = eval(a)
print(pow(num, 2))