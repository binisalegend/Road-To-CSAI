// /*
//  * @Descripttion: 
//  * @version: 
//  * @Author: binisalegend
//  * @Date: 2023-10-23 10:51:52
//  * @LastEditors: binisalegend
//  * @LastEditTime: 2023-10-23 10:57:14
//  */

#include <iostream>
#include <queue>
using namespace std;

struct TreeNode
{
    int weight;
    TreeNode* left;
    TreeNode* right;
};

struct CompareNodes
{
    bool operator()(TreeNode* a, TreeNode* b)
    {
        return a->weight > b->weight;
    }
};

int CalculateWPL(TreeNode* root, int depth)
{
    if (root == nullptr)
        return 0;

    if (root->left == nullptr && root->right == nullptr)
        return root->weight * depth;

    int leftWPL = CalculateWPL(root->left, depth + 1);
    int rightWPL = CalculateWPL(root->right, depth + 1);

    return leftWPL + rightWPL;
}

int main()
{
    priority_queue<TreeNode*, vector<TreeNode*>, CompareNodes> pq;

    int num = 0;
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        int loc = 0;
        cin >> loc;
        pq.push(new TreeNode{loc, nullptr, nullptr});
    }

    while (pq.size() > 1)
    {
        TreeNode* left = pq.top();
        pq.pop();

        TreeNode* right = pq.top();
        pq.pop();

        TreeNode* parent = new TreeNode{left->weight + right->weight, left, right};
        pq.push(parent);
    }

    TreeNode* root = pq.top();
    pq.pop();

    int wpl = CalculateWPL(root, 0);
    cout << "WPL=" << wpl << endl;

    system("pause");
    return 0;
}
