/*
 * @lc app=leetcode.cn id=133 lang=java
 *
 * [133] 克隆图
 */

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.HashMap;
import java.util.List;
import java.util.Queue;
// @lc code=start

// Definition for a Node.
class Node {
    public int val;
    public List<Node> neighbors;
    public Node() {
        val = 0;
        neighbors = new ArrayList<Node>();
    }
    public Node(int _val) {
        val = _val;
        neighbors = new ArrayList<Node>();
    }
    public Node(int _val, ArrayList<Node> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
}

class Solution {
    public Node cloneGraph(Node node) {
        if (node == null) return null;
        Node res = new Node(node.val);
        HashMap<Node, Node> map = new HashMap<>();
        map.put(node, res);
        Queue<Node> loc = new LinkedList<>();
        loc.add(node);
        while (!loc.isEmpty())
        {
            Node cur = loc.peek();
            loc.poll();
            for (Node neighbor: cur.neighbors)
            {
                if (!map.containsKey(neighbor))
                {
                    Node clone = new Node(neighbor.val);
                    map.put(neighbor, clone);
                    loc.add(neighbor);
                }
                map.get(cur).neighbors.add(map.get(neighbor));
            }
        }
        return res;
    }
}
// @lc code=end

