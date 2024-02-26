'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 22:39:23
LastEditors: binisalegend
LastEditTime: 2023-10-29 22:41:36
'''
NumList = input()

NumList = NumList.split(',')
MaxNum = 0
for num in range(len(NumList)):
    NumList[num] = int(NumList[num])
    if NumList[num] > MaxNum:
        MaxNum = NumList[num]
print(MaxNum)