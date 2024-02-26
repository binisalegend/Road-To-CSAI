'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 22:34:44
LastEditors: binisalegend
LastEditTime: 2023-10-29 22:38:10
'''
n = input("请输入一个数字：")
s = "〇一二三四五六七八九"
for c in "0123456789":
    n = n.replace(c, s[int(c)])
print(n)