/*
 * @lc app=leetcode.cn id=5 lang=java
 *
 * [5] 最长回文子串
 */

// @lc code=start
class Solution {
    public String longestPalindrome(String s) {
        int start = 0;
        int maxlen = 1;
        int length = s.length();
        boolean[][] dp = new boolean[length][length];

        for (int i = 0; i < length; i++) {
            dp[i][i] = true;
        }

        for (int j = 1; j < length; j++)
        {
            for (int i = 0; i < j; i++)
            {
                if (s.charAt(i) != s.charAt(j)) 
                {
                    dp[i][j] = false;
                }
                else
                {
                    if (j - i < 3) 
                    {
                        dp[i][j] = true;
                    }
                    else
                    {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }

                if (dp[i][j] == true && j - i + 1 > maxlen)
                {
                    maxlen = j - i + 1;
                    start = i;
                }
            }
        }

        return s.substring(start, start + maxlen);
    }
}
// @lc code=end

