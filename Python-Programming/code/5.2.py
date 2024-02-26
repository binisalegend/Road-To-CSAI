'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 21:01:49
LastEditors: binisalegend
LastEditTime: 2023-10-29 21:15:36
'''
import math
def prime(m):
    cnt = 0
    flag = False
    while cnt < 5:
        flag = False
        for j in range(2, m):
            if m % j == 0:
                m += 1
                flag = True
                break 
        if not flag:
            if cnt == 4:
                print(m, end='')
            else:
                print(m, end=',')
            m += 1
            cnt += 1

n = math.ceil(eval(input()))
prime(n)