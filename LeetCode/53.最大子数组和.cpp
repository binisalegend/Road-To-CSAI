/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */
#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = INT_MIN;
        int sum = 0;
        
        for (int num: nums)
        {
            sum += num;
            maxSum = max(maxSum, sum);
            if (sum < 0) sum = 0; // 感觉这个有点抽象啊，用这个加和小于0重置代替了可以从当前位开始取值的情况
        }
        return maxSum;
    }
};
// @lc code=end

