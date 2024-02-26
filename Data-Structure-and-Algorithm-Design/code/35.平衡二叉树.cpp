#include<bits/stdc++.h>
using namespace std;
#define N 1000000 
    
typedef struct treenode
{
    char data;
    int height;
    struct treenode *lchild;
    struct treenode *rchlid;
}TreeNode;

TreeNode *root;
int n;  

int height(TreeNode *tree)
{
    return tree == nullptr ? 0 : tree->height;
}

void UpdataHeight(TreeNode *tree)
{
    tree->height = max(height(tree->lchild), height(tree->rchlid)) + 1;
    return;
}

int BalanceFactor(TreeNode *tree)
{
    if (tree == nullptr) return 0;
    return height(tree->lchild) - height(tree->rchlid);
}

TreeNode* newNode(int key) {
    TreeNode *newnode = new TreeNode();
    if (newnode)
    {
        newnode->data = key;
        newnode->height = 1;
        newnode->lchild = newnode->rchlid = nullptr;
    }
    return newnode;
}

TreeNode *rightRotate(TreeNode *root) {
    TreeNode *newnode = root->lchild;
    root->lchild = newnode->rchlid;
    newnode->rchlid = root;
    root->height = max(height(root->lchild), height(root->rchlid)) + 1;
    newnode->height = max(height(newnode->lchild), height(newnode->rchlid)) + 1;
    return newnode;
}

TreeNode *leftRotate(TreeNode *root) {
    TreeNode *newnode = root->rchlid;
    root->rchlid = newnode->lchild;
    newnode->lchild = root;
    root->height = max(height(root->lchild), height(root->rchlid)) + 1;
    newnode->height = max(height(newnode->lchild), height(newnode->rchlid)) + 1;
    return newnode;
}

TreeNode* insert(TreeNode* node, int data) 
{
    if (node == NULL)
        return(newNode(data));
    if (data < node->data)
        node->lchild = insert(node->lchild, data);
    else if (data > node->data)
        node->rchlid = insert(node->rchlid, data);
    else
        return node;

    node->height = 1 + max(height(node->lchild), height(node->rchlid));

    int balance = BalanceFactor(node);

    if (balance > 1) 
    {
        if ((node->lchild != NULL) && (BalanceFactor(node->lchild) >= 0)) 
        {
            return rightRotate(node);
        }
        else 
        {
            node->lchild = leftRotate(node->lchild);
            return rightRotate(node);
        }
    }
 
    if (balance < -1) 
    {
        if ((node->rchlid != NULL) && (BalanceFactor(node->rchlid) <= 0)) 
        {
            return leftRotate(node);
        }
        else 
        {
            node->rchlid = rightRotate(node->rchlid);
            return leftRotate(node);
        }
    }
    return node;
}

void VisualizeTree(TreeNode *tree, int n)
{
    if (tree == NULL) return;
    n += 4;
    VisualizeTree(tree->rchlid, n);
    for (int i = 4; i < n; i++)
    {
        cout << " ";
    }
    cout << tree->data << endl;
    VisualizeTree(tree->lchild, n);
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

int main()
{
    string str;
    cin >> str;
    TreeNode *root = NULL;

    for (char c: str)
    {
        root = insert(root, c);
    }

    cout << "Preorder: ";
    PreOrder(root);
    cout << endl;

    cout << "Inorder: ";
    InOrder(root);
    cout << endl;

    cout << "Postorder: ";
    PostOrder(root);
    cout << endl;

    cout << "Tree:" << endl;
    VisualizeTree(root, 0);

    return 0;
}