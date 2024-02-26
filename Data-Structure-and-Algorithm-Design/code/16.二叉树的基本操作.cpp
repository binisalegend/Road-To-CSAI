/*
 * @Descripttion:  the basic operation of tree
 * @version: 1.0.0
 * @Author: binisalegend
 * @Date: 2023-10-21 09:24:28
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-21 14:01:47
 */
#include<bits/stdc++.h>
using namespace std;
#define N 1000000 
    
typedef struct treenode
{
    char data;
    struct treenode *lchild;
    struct treenode *rchlid;
}TreeNode;

TreeNode *root;
char str[N] = "";    
int n;


/**
 * @name: CreateTree
 * @msg: initialate the tree struct
 * @return {*}
 */
TreeNode *CreateTree()
{
    if (n >= strlen(str))
    {
        return NULL;
    }
    if (str[n] == '#')
    {
        n++;
        return NULL;
    }
    TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
    p->data = str[n++];
    p->lchild = CreateTree();
    p->rchlid = CreateTree();
    return p;
}

void VisualizeTree(TreeNode *tree, int n)
{
    int count = n;
    if (tree != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            cout << " ";
        }
        cout << tree->data << endl;
        VisualizeTree(tree->lchild, 4 + n);
        VisualizeTree(tree->rchlid, 4 + n);
    }
    return;
}

void PreOrder(TreeNode *tree)
{
    if (tree != NULL)
    {
        cout << tree->data;
        PreOrder(tree->lchild);
        PreOrder(tree->rchlid);
    }
    return;
}

void InOrder(TreeNode *tree)
{
    if (tree != NULL)
    {
        InOrder(tree->lchild);
        cout << tree->data;
        InOrder(tree->rchlid);
    }
    return;
}

void PostOrder(TreeNode *tree)
{
    if (tree != NULL)
    {
        PostOrder(tree->lchild);
        PostOrder(tree->rchlid);
        cout << tree->data;
    }
    return;
}

/**
 * @name: ExangeTree
 * @msg: exchange left and right child tree
 * @param {TreeNode} *tree
 * @return {*}
 */
void ExchangeTree(TreeNode *tree)
{
    if (tree == NULL)  return;
    TreeNode *loc;
    loc = tree->lchild;
    tree->lchild = tree->rchlid;
    tree->rchlid = loc;
    ExchangeTree(tree->lchild);
    ExchangeTree(tree->rchlid);
}

/**
 * @name: CountingNumLeaf
 * @msg: outputing the number of leaf node
 * @param {TreeNode} *tree
 * @return {*}
 */
int CountingNumOfLeaf(TreeNode *tree)
{
    int count = 0;
    if (tree != NULL)
    {
        if (tree->lchild == NULL && tree->rchlid == NULL)
        {
            count++;
        }
        count += CountingNumOfLeaf(tree->lchild);
        count += CountingNumOfLeaf(tree->rchlid);
    }
    return count;
}

int main()
{
    cin >> str;
    n = 0;
    TreeNode *root = CreateTree();

    cout << "BiTree" << endl;

    n = 0;
    VisualizeTree(root, 0);

    cout << "pre_sequence  : ";
    PreOrder(root);
    cout << endl;

    cout << "in_sequence   : ";
    InOrder(root);
    cout << endl;

    cout << "post_sequence : ";
    PostOrder(root);
    cout << endl;

    int count = CountingNumOfLeaf(root);
    cout << "Number of leaf: ";
    cout << count << endl;

    ExchangeTree(root);

    cout << "BiTree swapped" << endl;

    n = 0;
    VisualizeTree(root, 0);

    cout << "pre_sequence  : ";
    PreOrder(root);
    cout << endl;

    cout << "in_sequence   : ";
    InOrder(root);
    cout << endl;

    cout << "post_sequence : ";
    PostOrder(root);
    cout << endl;

    return 0;
}