import numpy as np
import random
import time
from utils import calculate_time

time_record = 0

def PSO(times, n, m, num_particles=50, max_iter=1000, w_max=0.9, w_min=0.4, c1_initial=1.49445, c2_initial=1.49445):
    begin = time.time()
    # 初始化粒子群
    particles = [list(np.random.permutation(n)) for _ in range(num_particles)]
    velocities = [np.zeros(n) for _ in range(num_particles)]
    personal_best_positions = particles.copy()
    personal_best_scores = [calculate_time(times, p, n, m)[-1][-1] for p in particles]

    global_best_position = personal_best_positions[np.argmin(personal_best_scores)]
    global_best_score = min(personal_best_scores)

    # 主循环
    for iteration in range(max_iter):
        # 动态调整惯性权重
        w = w_max - (w_max - w_min) * iteration / max_iter
        c1 = c1_initial
        c2 = c2_initial
        
        for i in range(num_particles):
            # 更新速度和位置
            r1, r2 = random.random(), random.random()
            velocities[i] = (w * velocities[i] +
                             c1 * r1 * (np.array(personal_best_positions[i]) - np.array(particles[i])) +
                             c2 * r2 * (np.array(global_best_position) - np.array(particles[i])))
            particles[i] = (np.array(particles[i]) + velocities[i]).astype(int).tolist()
            
            # 修正粒子位置
            particles[i] = fix_position(particles[i], n)
            
            # 计算新的适应度值
            current_score = calculate_time(times, particles[i], n, m)[-1][-1]
            
            # 更新个体最优解
            if current_score < personal_best_scores[i]:
                personal_best_scores[i] = current_score
                personal_best_positions[i] = particles[i]
            
            # 更新全局最优解
            if current_score < global_best_score:
                global_best_score = current_score
                global_best_position = particles[i]
    
    end = time.time()
    total_time = end - begin

    return calculate_time(times, global_best_position, n, m), global_best_score, global_best_position, total_time

def fix_position(particle, n):
    particle = np.clip(particle, 0, n-1).tolist()
    unique_elements, counts = np.unique(particle, return_counts=True)
    # counts 保持为 numpy 数组，不需要转换为列表
    duplicates = unique_elements[counts > 1]
    missing_elements = list(set(range(n)) - set(particle))
    
    for dup in duplicates:
        for _ in range(counts[np.where(unique_elements == dup)][0] - 1):  # 使用 np.where 获取索引
            particle[particle.index(dup)] = missing_elements.pop(0)
    
    return particle

def PSO_with_restarts(times, n, m, num_particles=30, max_iter=1000, w_max=0.9, w_min=0.4, c1_initial=2, c2_initial=2, num_restarts=10):
    best_global_score = float('inf')
    best_global_position = None
    best_global_time_result = None
    
    for j in range(num_restarts):
        time_result, global_score, global_position, total_time = PSO(times, n, m, num_particles, max_iter, w_max, w_min, c1_initial, c2_initial)
        if global_score < best_global_score:
            best_global_score = global_score
            best_global_position = global_position
            best_global_time_result = time_result
            time_record = total_time

        print('第', j, '次模拟退火结束', '最优解为：', time_result, '，最优调度序列为：', global_position)
            
    return best_global_time_result, best_global_score, best_global_position, time_record
