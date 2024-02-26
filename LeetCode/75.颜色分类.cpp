/*
 * @lc app=leetcode.cn id=75 lang=cpp
 *
 * [75] 颜色分类
 */
#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int num_0 = 0, num_1 = 0, num_2 = 0;
        for (int num: nums)
        {
            if (num == 0) num_0++;
            else if (num == 1) num_1++;
            else num_2++;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (i < num_0) nums[i] = 0;
            else if (i < num_0 + num_1) nums[i] = 1;
            else nums[i] = 2;
        }
    }
};
// @lc code=end

