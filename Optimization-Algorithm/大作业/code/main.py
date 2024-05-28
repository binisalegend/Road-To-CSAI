import random

from Dataloader import read
from plot import plot_gantt
from SA import SA
from PSO import PSO_with_restarts

T0 = 1000  # 初始温度
T = T0  # 当前温度
alpha = 0.999  # 退火率
critical_T = 0.0001  # 退火临界温度

num_particles = 50 # 粒子群数量
max_iter = 1000  # 最大迭代次数
w_max = 0.9  # 惯性权重最大值
w_min = 0.4  # 惯性权重最小值
c1_initial = 1.49445  # 个体学习因子
c2_initial = 1.49445  # 群体学习因子

Time_record = 0


f = open('data.txt', 'r', encoding='utf-8')

for i in range(0, 11):
    f.readline(); f.readline()
    # 处理数据格式
    n, m = f.readline().replace('  ', ' ').split(' ')
    n, m = int(n), int(m)
    times = read(n, f)

    schedule = []
    result = 1e10  # 当前解的时间
    schedule = list(range(len(times)))
    random.shuffle(schedule)  # 直接对列表进行操作

    # 进行多次模拟退火，如果得到的新解时间更短，则接受
    for j in range(20):
        time, min_time, schedule, total_time = SA(schedule, times, n, m, alpha, T, critical_T, i, j)
        if min_time < result:
            result = min_time
            time_result = time.copy()
            Time_record = total_time
            best_schedule = schedule

    print('第', i, '组数据的最优解为：', result, '，最优调度序列为：', best_schedule, '，单轮时间为：', Time_record)

    plot_gantt(time_result, times, best_schedule, i, n, m)

    # 粒子群优化算法，多次运行并选择最优解
    num_restarts = 10
    time_result_pso, result_pso, best_schedule_pso, Time_record = PSO_with_restarts(times, n, m, num_particles, max_iter, w_max, w_min, c1_initial, c2_initial, num_restarts)

    print('第', i, '组数据的粒子群优化最优解为：', result_pso, '，最优调度序列为：', best_schedule_pso, '，单轮时间为：', Time_record)

    plot_gantt(time_result_pso, times, best_schedule_pso, i, n, m)
