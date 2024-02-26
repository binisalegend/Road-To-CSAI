#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maximumPathSum(std::vector<std::vector<int>>& triangle) {
    int n = triangle.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    // 初始化最底部的路径和
    for (int i = 0; i < n; i++) {
        dp[n-1][i] = triangle[n-1][i];
    }

    // 从倒数第二行开始计算最大路径和
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = triangle[i][j] + std::max(dp[i+1][j], dp[i+1][j+1]);
        }
    }

    return dp[0][0];
}

int main() 
{
    int line = 0;
    scanf("%d", &line);
    std::vector<std::vector<int>> triangle(line, std::vector<int>(line, 0));
    for (int i = 0; i < line; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }

    int maxSum = maximumPathSum(triangle);
    std::cout << maxSum << std::endl;

    return 0;
}
