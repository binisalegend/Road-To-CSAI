/*
 * @lc app=leetcode.cn id=2 lang=java
 *
 * [2] 两数相加
 */

// @lc code=start

class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val) { 
        this.val = val; 
    }
    ListNode(int val, ListNode next) { 
        this.val = val; 
        this.next = next; 
    }
}


class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode result = new ListNode();
        ListNode loc = result;
        int carrybits = 0;

        int sum = l1.val + l2.val + carrybits;
        carrybits = sum / 10;
        sum = sum % 10;
        result.val = sum;

        while ((l1.next != null) && (l2.next != null))
        {
            l1 = l1.next;
            l2 = l2.next;
            result.next = new ListNode();
            result = result.next;
            sum = l1.val + l2.val + carrybits;
            carrybits = sum / 10;
            sum = sum % 10;
            result.val = sum;
        }        

        while (l1.next != null)
        {
            l1 = l1.next;
            result.next = new ListNode();
            result = result.next;
            int tmp = l1.val + carrybits;
            carrybits = tmp / 10;
            tmp = tmp % 10;
            result.val = tmp;
        }
        while (l2.next != null)
        {
            l2 = l2.next;            
            int tmp = l2.val + carrybits;
            result.next = new ListNode();
            result = result.next;
            carrybits = tmp / 10;
            tmp = tmp % 10;
            result.val = tmp;
        }
        if (carrybits != 0)
        {
            result.next = new ListNode();
            result = result.next;
            result.val = carrybits;
            result.next = null;
        }
        return loc;
    }
}
// @lc code=end

