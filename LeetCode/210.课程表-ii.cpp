/*
 * @lc app=leetcode.cn id=210 lang=cpp
 *
 * [210] 课程表 II
 */
#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> ans;
        int n = prerequisites.size();
        if (numCourses < 2) {
            for (int i = 0; i < numCourses; i++)
            {
                ans.push_back(i);
            }
            return ans;
        }
        map<int, vector<int>> Graph;
        int InDgree[numCourses];
        memset(InDgree, 0, sizeof(InDgree));
        for (auto lesson: prerequisites)
        {
            Graph[lesson[1]].push_back(lesson[0]);
            InDgree[lesson[0]]++;
        }

        queue<int> InDgreeZero;
        for (int i = 0; i < numCourses; i++)
        {
            if (InDgree[i] == 0)
            {
                InDgreeZero.push(i);
            }
        }

        while (!InDgreeZero.empty())
        {
            int lesson = InDgreeZero.front();
            InDgreeZero.pop();
            for (auto i: Graph[lesson])
            {
                InDgree[i]--;
                if (InDgree[i] == 0)
                {
                    InDgreeZero.push(i);
                }
                n--;
            }
            ans.push_back(lesson);
        }
        if (n != 0) 
        {
            ans.clear();
            return ans;
        }
        return ans;
    }
};
// @lc code=end

