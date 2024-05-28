import numpy as np
import random

def point_neighbor(s):
    # 随机选择两个点进行交换
    i = random.randint(0, len(s) - 1)
    j = random.randint(0, len(s) - 1)
    while i == j:
        j = random.randint(0, len(s) - 1)
    
    s[i], s[j] = s[j], s[i]  # 直接交换
    return s

def calculate_time(times, schedule, n, m):
    # 创造一个新数组（n行m列），用于第j个工件在第i个机器加工时所需的总加工时间（包括等待）
    total_every_time = np.zeros((n, m))
    # 第一个工件在第一台机器上的所需时间
    total_every_time[0][0] = times[schedule[0]][0]

    # a[0][j]表示到j机器第一个工件总加工时间，a[0][-1]表示第一个工件的总加工时间
    for j in range(1, m):
        total_every_time[0][j] = total_every_time[0][j - 1] + times[schedule[0]][j]

    # a[i][0]表示第一个机器加工到第i个工件的总加工时间，a[-1][0]表示第一个机器加工所有工件的总加工时间
    for i in range(1, n):
        total_every_time[i][0] = total_every_time[i - 1][0] + times[schedule[i]][0]

    # 填充
    for j in range(1, m):
        for i in range(1, n):
            total_every_time[i][j] = max(total_every_time[i - 1][j], total_every_time[i][j - 1]) + times[schedule[i]][j]
    
    return total_every_time
