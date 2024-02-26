'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 16:25:18
LastEditors: binisalegend
LastEditTime: 2023-10-29 16:28:27
'''
import random

random.seed(123)
s = 0
num = eval(input())
for i in range(num):
    x, y = random.random(), random.random()
    r = pow(pow(x, 2) + pow(y, 2), 0.5)
    if r <= 1:
        s += 1

pi = 4 * s / num
print("{:.6f}".format(pi))    
