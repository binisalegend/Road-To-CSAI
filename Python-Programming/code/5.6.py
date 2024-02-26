'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 21:47:07
LastEditors: binisalegend
LastEditTime: 2023-10-29 21:49:21
'''
def fibonacci(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return  fibonacci(n - 1) +  fibonacci(n - 2)
    
n = eval(input())

for i in range(1, n+1):
    if i == n:
        print(fibonacci(i))
        break
    print(fibonacci(i), end = ",")
