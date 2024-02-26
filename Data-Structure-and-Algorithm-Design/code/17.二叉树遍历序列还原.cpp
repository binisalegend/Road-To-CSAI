/*
 * @Descripttion: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-21 14:02:43
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-22 13:47:11
 */
#include<bits/stdc++.h>
using namespace std;

typedef struct treenode
{
    char data = -1;
    struct treenode *lchild, *rchild;
}TreeNode;

    
/**
 * @name: CreateTree 
 * @msg: Create a tree through InOrder string and PostOrder string
 * @param {string} InOrder
 * @param {string} PostOrder
 * @param {  } PreOrder
 * @return {*}
 */
TreeNode *CreateTree(string InOrder, string PostOrder) 
{
    int length = InOrder.length();
    if (length == 0)
    {
        return NULL;
    }
    else if (length == 1)
    {
        TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
        p->data = InOrder[0];
        p->lchild = NULL;
        p->rchild = NULL;
        return p;
    }
    else 
    {
        int position = InOrder.find(PostOrder[length-1]);
        TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
        p->data = PostOrder[length-1];
        p->lchild = CreateTree(InOrder.substr(0, position), PostOrder.substr(0, position));
        p->rchild = CreateTree(InOrder.substr(position+1, length-position-1), PostOrder.substr(position, length-position-1));
        return p;
    }
}

void LevelOrder(TreeNode *tree)
{
    queue<TreeNode *> LevelTree;
    TreeNode *p = tree;
    LevelTree.push(p);

    while (!LevelTree.empty())
    {
        p = LevelTree.front();
        cout << p->data;
        LevelTree.pop();
        if (p->lchild != NULL)
        {
            LevelTree.push(p->lchild);
        }
        if (p->rchild != NULL)
        {
            LevelTree.push(p->rchild);
        }
    }
}

int main()
{
    string str1, str2;

    cin >> str1 >> str2;
    TreeNode *root = CreateTree(str1, str2);
    LevelOrder(root);
    cout << endl;
    system("pause");
    return 0;
}