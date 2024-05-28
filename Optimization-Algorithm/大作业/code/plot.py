import matplotlib.pyplot as plt
from colour import Color
import numpy as np


def plot_gantt(a, times, schedule, i, n, m):
    plt.rcParams['font.sans-serif'] = ['SimHei']

    # 创建数组c，用于存放确定序列中每个工件在每个机器的开始加工时间
    c = np.zeros((n, m))
    for j in range(n):
        for k in range(m):
            c[j][k] = a[j][k] - times[schedule[j]][k]

    # 创建数组d，将c按工件序号从0开始的顺序重新排列
    d = np.zeros((n, m))
    for k in range(n):
        d[schedule[k]][:] = c[k][:]

    # 设置画布大小和分辨率
    plt.figure(figsize=(20, 15), dpi=200)

    # 设置一组颜色
    red = Color("red")
    colors = list(red.range_to(Color("purple"), n))
    colors = [color.rgb for color in colors]

    # barh:水平柱状图，设置循坏迭代以绘制层叠效果
    for j in range(m-1):
        for k in range(n):
            plt.barh(y = j + 1, width=times[k][j], left=d[k][j], color=colors[k])
    for k in range(n):
        plt.barh(y = m, width=times[k][m-1], left=d[k][m-1], color=colors[k], label='工件' + str(k))

    # 显示图例
    plt.legend(fontsize=5, loc="lower right")

    # XY轴标签
    plt.title("instance" + str(i) + "甘特图", fontsize=13, loc="center")
    plt.xlabel("加工时间", fontsize=12)
    plt.ylabel("机器", fontsize=12)
    plt.show()