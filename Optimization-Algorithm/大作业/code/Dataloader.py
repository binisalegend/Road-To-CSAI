import matplotlib as plt
import numpy as np

# f = open('data.txt', 'r', encoding='utf-8')

# 数据读入
def read(n, f):
    # times代表加工时间的列表
    times = []
    for i in range(n):
        # r代表读入的每一行，注意：给出的数据中为了对齐机器号，有多个空格(2个和3个)会影响切分，所以要把多个空格都改为1个，并去除每一行的换行符
        r = f.readline().replace('\n', '').replace('   ', ' ').replace('  ', ' ').split(' ')
        # 1::2代表从第二个数开始隔一个一取，这样就能将对应的加工时间得出
        times.append(r[1::2])
    
    times = np.array(times, dtype=int).tolist()
    return times