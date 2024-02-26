/*
 * @lc app=leetcode.cn id=999 lang=cpp
 *
 * [999] 可以被一步捕获的棋子数
 */
        
#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        map<pair<int, int>, char> graph;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0;j < 8; ++j) {
                if (board[i][j] == 'R') {
                    return dfs(board, i, j, 0, 1) + dfs(board, i, j, 0, -1) + dfs(board, i, j, 1, 0) + dfs(board, i, j, -1, 0);
                }
            }
        }
        return 0;
    }

    int dfs(vector<vector<char>>& board, int x, int y, int dx, int dy) {
        if (x < 0 || x >= 8 || y < 0 || y >= 8 || board[x][y] == 'B') return 0;
        if (board[x][y] == 'p') return 1;
        return dfs(board, x + dx, y + dy, dx, dy);
    }
};
// @lc code=end

