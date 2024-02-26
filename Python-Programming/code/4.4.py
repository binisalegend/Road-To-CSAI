'''
Descripttion: 
version: 
Author: binisalegend
Date: 2023-10-22 21:53:30
LastEditors: binisalegend
LastEditTime: 2023-10-22 21:56:15
'''
s = input("")  # 输入包含中文的字符串
count = 0

for char in s:  # 遍历输入字符串的每个字符
    if '\u4E00' <= char <= '\u9FA5':  # 使用Unicode编码范围来检查中文字符
        count += 1

print(count)
