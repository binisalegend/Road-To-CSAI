'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 21:22:08
LastEditors: binisalegend
LastEditTime: 2023-10-29 21:28:06
'''
# 请在...补充一行或多行代码
steps = 0
def hanoi(src, des, mid, n):
    global steps
    if n == 1:
        steps += 1
        print("[STEP{:>4}] {}->{}".format(steps, src, des))
    else:
        hanoi(src, mid, des, n-1)
        hanoi(src, des, mid, 1)
        hanoi(mid, des, src, n-1)
        

N = eval(input())
hanoi("A", "C", "B", N)
