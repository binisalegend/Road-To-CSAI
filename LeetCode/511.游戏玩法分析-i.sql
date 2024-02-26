--
-- @lc app=leetcode.cn id=511 lang=mysql
--
-- [511] 游戏玩法分析 I
--

-- @lc code=start
# Write your MySQL query statement below

SELECT
    player_id,
    MIN(event_date) AS first_login
FROM Activity
GROUP BY player_id

-- @lc code=end

