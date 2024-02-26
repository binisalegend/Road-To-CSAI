'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 21:36:08
LastEditors: binisalegend
LastEditTime: 2023-10-29 21:45:57
'''
#请在...补充代码
import random
import math

def genpwd(length):
    return random.randint(math.pow(10, length-1), math.pow(10, length))

length = eval(input())
random.seed(17)
for i in range(3):
    print(genpwd(length))