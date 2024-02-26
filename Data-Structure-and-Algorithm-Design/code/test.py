def edit_distance(str1, str2):
    m = len(str1)
    n = len(str2)

    # 创建一个二维数组来存储编辑距离
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # 初始化第一行和第一列
    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j

    # 计算编辑距离
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if str1[i - 1] == str2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = min(dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]) + 1

    return dp[m][n]

# 测试
str1 = "kitten"
str2 = "sitting"
distance = edit_distance(str1, str2)
print(f"The edit distance between '{str1}' and '{str2}' is {distance}.")
