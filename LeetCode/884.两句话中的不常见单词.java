/*
 * @lc app=leetcode.cn id=884 lang=java
 *
 * [884] 两句话中的不常见单词
 */

// @lc code=start
import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;

class Solution {
    public String[] uncommonFromSentences(String s1, String s2) {
        String[] str1 = s1.split(" ");
        String[] str2 = s2.split(" ");
        String[] res = new String[str1.length + str2.length];
        Map<String, Integer> map = new HashMap<>();
        for (String s : str1) {
            map.put(s, map.getOrDefault(s, 0) + 1);
        }
        for (String s : str2) {
            map.put(s, map.getOrDefault(s, 0) + 1);
        }
        int index = 0;
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            if (entry.getValue() == 1) {
                res[index++] = entry.getKey();
            }
        }
        return Arrays.copyOfRange(res, 0, index);
    }
}
// @lc code=end

