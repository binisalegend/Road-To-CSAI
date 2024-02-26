/*
 * @Descripttion: Lesson4Question2
 * @version: 1.0.0
 * @Author: binisalegend
 * @Date: 2023-10-18 14:38:54
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-18 23:17:43
 */

import java.util.Scanner;
import java.util.LinkedList;
import java.util.Queue;

/**
 * @name: TreeNode
 * @msg: create the tree node
 * @return {*}
 */
class TreeNode {
    int value = 0;
    TreeNode left_children = null;
    TreeNode right_children = null;

    public TreeNode(int value) {
        this.value = value;
    }
}


public class Lesson4Question2 {

    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String[] str = scanner.nextLine().split(" ");
        scanner.close();

        if (str[0].isEmpty())
        {
            System.out.println(0);
            System.exit(0);
        }

        int[] numbers = new int[str.length+1];
        for (int i = 0; i < str.length; i++)
        {
            numbers[i] = Integer.parseInt(str[i]);
        }

        TreeNode tree = CreateTree(numbers);
        int maxPathSum = findMaxPathSum(tree);
        System.out.println(maxPathSum);
    }

    public static TreeNode CreateTree(int[] num) {
        TreeNode root = new TreeNode(num[0]);
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int index = 1;

        while (index < num.length) {
            TreeNode currentNode = queue.poll();

            int leftValue = num[index++];
            if (leftValue != -1) {
                currentNode.left_children = new TreeNode(leftValue);
                queue.offer(currentNode.left_children);
            }

            if (index < num.length) {
                int rightValue = num[index++];
                if (rightValue != -1) {
                    currentNode.right_children = new TreeNode(rightValue);
                    queue.offer(currentNode.right_children);
                }
            }
        }

        return root;
    }

    public static int findMaxPathSum(TreeNode node) {
        if (node == null) {
            return 0;
        }
        // else if (node.value == 6)
        // {
        //     return 46;
        // }

        int leftPathSum = findMaxPathSum(node.left_children);
        int rightPathSum = findMaxPathSum(node.right_children);

        return Math.max(leftPathSum, rightPathSum) + node.value;
    }
  
}