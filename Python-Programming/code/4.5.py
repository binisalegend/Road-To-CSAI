'''
Descripttion: 
version: 
Author: binisalegend
Date: 2023-10-22 21:57:47
LastEditors: binisalegend
LastEditTime: 2023-10-22 22:00:30
'''
import random

a = eval(input())
random.seed(a)

loc = 'ABCDEFGHIJ0123456789'
for i in range(6):
    a = random.choice(loc)
    print(a, end='')
