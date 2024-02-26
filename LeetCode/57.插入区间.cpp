/*
 * @lc app=leetcode.cn id=57 lang=cpp
 *
 * [57] 插入区间
 */
#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        if (intervals.empty()) return ans.push_back(newInterval), ans;
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end());

        // cout << intervals[0][0] << " " << intervals[0][1] << endl;
        // cout << intervals[1][0] << " " << intervals[1][1] << endl;
        // cout << intervals[2][0] << " " << intervals[2][1] << endl;
        // cout << intervals[3][0] << " " << intervals[3][1] << endl;

        int left = intervals[0][0], right = intervals[0][1];
        for (auto& interval : intervals) 
        {
            if (interval[0] <= right) 
            {
                right = max(right, interval[1]);
            } 
            else 
            {
                ans.push_back({left, right});
                left = interval[0];
                right = interval[1];
            }
        }
        ans.push_back({left, right});
        return ans;
    }
};
// @lc code=end

