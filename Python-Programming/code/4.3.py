'''
Descripttion: 
version: 
Author: binisalegend
Date: 2023-10-22 21:35:20
LastEditors: binisalegend
LastEditTime: 2023-10-22 21:53:27
'''
import random

a, b = input().split(",")
c = eval(a) + eval(b)

random.seed(c)

for i in range(20):
    num = random.randint(32, 127)
    print(chr(num), end='')