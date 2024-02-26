'''
Description: 
version: 
Author: binisalegend
Date: 2023-10-29 22:29:38
LastEditors: binisalegend
LastEditTime: 2023-10-29 22:31:23
'''
def peach(n):
    if (n == 10):
        return 1
    return (peach(n+1)+1) * 2
    
for i in range(10,0,-1):
    print("第{}天有{}只桃子".format(i,peach(i)))