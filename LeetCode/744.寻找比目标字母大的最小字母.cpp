/*
 * @lc app=leetcode.cn id=744 lang=cpp
 *
 * [744] 寻找比目标字母大的最小字母
 */

// @lc code=start
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        char str = letters.front();
        reverse(letters.begin(),letters.end());
        while (!letters.empty())
        {
            char ch = letters.back();
            letters.pop_back();
            if (ch > target)
            {
                return ch;
            }
        }
        return str;
    }
};
// @lc code=end

