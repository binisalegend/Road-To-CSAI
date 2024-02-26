'''
Descripttion: 
version: 
Author: binisalegend
Date: 2023-10-22 21:12:06
LastEditors: binisalegend
LastEditTime: 2023-10-22 21:19:39
'''

for i in range(100, 1000):
    local = i
    num = 0
    for j in range(3):
        num += pow(i % 10, 3)
        i = i // 10
    if num == local:
        print(local, end=',')