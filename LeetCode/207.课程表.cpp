/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 */
#include<bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if (numCourses < 2) return true;
        int EdgeNum = prerequisites.size();
        int InDegree[numCourses];
        memset(InDegree, 0, sizeof(InDegree));
        map<int, vector<int>> Graph;
        for (auto lesson: prerequisites) {
            InDegree[lesson[0]]++;
            Graph[lesson[1]].push_back(lesson[0]);
        }

        queue<int> InDegreeZero;
        for (int i = 0; i < numCourses; i++)
        {
            if (InDegree[i] == 0)
            {
                InDegreeZero.push(i);
            }
        }

        while (!InDegreeZero.empty())
        {
            int lesson = InDegreeZero.front();
            InDegreeZero.pop();
            for (auto i: Graph[lesson])
            {
                InDegree[i]--;
                EdgeNum--;
                if (InDegree[i] == 0)
                {
                    InDegreeZero.push(i);
                }
            }
        }

        if (EdgeNum != 0) return false;
        return true;
    }
};
// @lc code=end

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edges(numCourses);
        vector<int> indeg(numCourses);
        for (auto& info : prerequisites) {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }
        int visited = 0;
        while (!q.empty()) {
            ++visited;
            int u = q.front();
            q.pop();
            for (int v: edges[u]) {
                --indeg[v];
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }
        return visited == numCourses;
    }
};

