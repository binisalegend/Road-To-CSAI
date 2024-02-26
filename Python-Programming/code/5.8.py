'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 22:32:22
LastEditors: binisalegend
LastEditTime: 2023-10-29 22:33:27
'''
def mean(numlist):
    s = 0.0
    for num in numlist:
        s = s + num
    return s / len(numlist)

#请输入一个列表：
ls = eval(input())
print("average:", mean(ls))