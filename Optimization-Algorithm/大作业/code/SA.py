from utils import point_neighbor, calculate_time

import numpy as np
import random
import time

random.seed(2024)

def SA(schedule, times, n, m, alpha, T, critical_T, i, j):
    begin = time.time()
    # 记录每次循环最小总时间的序列
    min_time = []
    time_split = calculate_time(times, schedule, n, m)
    current_time = time_split[-1][-1]
    min_time.append(current_time)

    while T > critical_T:  # 当前温度小于退火临界温度，结束算法
        new_schedule = point_neighbor(schedule[:])  # 确保不修改原始调度
        new_a = calculate_time(times, new_schedule, n, m)
        new_time = new_a[-1][-1]
        
        if new_time < current_time or random.random() < np.exp(-(new_time - current_time) / T):  # 时间差值小于0或者以一定概率接受
            schedule = new_schedule
            current_time = new_time
            time_split = new_a

        min_time.append(current_time)
        T *= alpha
    
    print('第', i, '组数据的第', j, '次模拟退火结束', '最优解为：', min_time[-1], '，最优调度序列为：', schedule)

    end = time.time()
    total_time = end - begin
    return time_split, min_time[-1], schedule, total_time