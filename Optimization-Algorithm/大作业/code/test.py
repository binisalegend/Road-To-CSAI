from utils import calculate_time
from Dataloader import read
import numpy as np

test = [9, 12, 3, 16, 10, 4, 13, 6, 11, 8, 17, 14, 1, 15, 0, 7, 2, 5]

f = open('test.txt', 'r', encoding='utf-8')

def test_calculate_time():
    f.readline(); f.readline()
    # 处理数据格式
    n, m = f.readline().replace('  ', ' ').split(' ')
    n, m = int(n), int(m)
    times = read(n, f)

    time = calculate_time(times, test, n, m)
    print(time[-1][-1])

test_calculate_time()