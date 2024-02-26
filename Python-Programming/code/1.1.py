'''
Description: 
version: 
Author: binisalegend
Date: 2023-09-27 22:18:58
LastEditors: binisalegend
LastEditTime: 2023-10-30 10:35:14
'''
money = input()
if money[0:3] == "RMB":
    num = eval(money[3:]) / 6.78
    print("USD", end='')
    print("{:.2f}".format(num))
else:
    num = eval(money[3:]) * 6.78
    print("RMB", end='')
    print("{:.2f}".format(num))
