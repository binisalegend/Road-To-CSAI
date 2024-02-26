# 定义函数来计算最少需要选择的特殊位置数
def min_special_positions(matrix_list):
    unique_positions = set()  # 用来存储不同矩阵的特殊位置

    for i in range(len(matrix_list) - 1):
        for j in range(i + 1, len(matrix_list)):
            found = False
            for x in range(len(matrix_list[i])):
                for y in range(len(matrix_list[i][0])):
                    if matrix_list[i][x][y] != matrix_list[j][x][y]:
                        unique_positions.add((x, y))
                        found = True
                        break
                if found:
                    break

    return len(unique_positions)

# 输入数据
T = int(input())  # 数据组数

for _ in range(T):
    n, m, k = map(int, input().split())  # 矩阵大小和个数
    matrix_list = []  # 存储每个01矩阵
    for _ in range(k):
        matrix = []
        for _ in range(n):
            row = input().strip()
            matrix.append(row)
        matrix_list.append(matrix)

    # 计算最少需要选择的特殊位置数并输出
    result = min_special_positions(matrix_list)
    print(result)
