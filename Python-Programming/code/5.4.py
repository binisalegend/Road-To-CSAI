'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 21:28:30
LastEditors: binisalegend
LastEditTime: 2023-10-29 21:35:52
'''
def SumOfSequence(n):
    if n % 2 == 0:
        sum = 0
        i = 2
        while i <= n:
            sum += 1 / i
            i += 2
        print("{:.2f}".format(sum))
    else:
        sum = 0
        i = 1
        while i <= n:
            sum += 1 / i
            i += 2
        print("{:.2f}".format(sum))

SumOfSequence(int(input()))
