#include<bits/stdc++.h>
using namespace std;
    
typedef struct treenode
{
    int data;
    struct treenode *lchild = NULL;
    struct treenode *rchlid = NULL;
}TreeNode;

map<int, int> TreeNodeBackSpace;
vector<int> TreeNodeStore;
vector<int> InOrderStore;

void CreateTree(TreeNode *tree, int val)  //建立排序二叉树
{	
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));  
	node->data = val;
	node->lchild = NULL;
	node->rchlid = NULL;
	TreeNode *temp = tree; 

	while (temp != NULL) 
    {
		if (val < temp->data) 
        {  
			if (temp->lchild == NULL) 
            {  
				temp->lchild = node;
				return;
			}
			else 
            {
				temp = temp->lchild;  
			}
		}
		else 
        {
			if (temp->rchlid == NULL) 
            {
				temp->rchlid = node;
				return;
			}
			else 
            {
				temp = temp->rchlid;  
			}
		}
	}
}

void CalculateTreeNodeBackSpace(TreeNode *tree, int n)
{
    if (tree != NULL)
    {
        TreeNodeBackSpace[tree->data] = n;
        CalculateTreeNodeBackSpace(tree->lchild, 4 + n);
        CalculateTreeNodeBackSpace(tree->rchlid, 4 + n);
    }
    return;
}

void VisualizeTree(TreeNode *tree, int n)
{
    for (int i = 0; i < InOrderStore.size(); i++)
    {
        for (int j = 0; j < TreeNodeBackSpace[InOrderStore[i]]; j++)
        {
            cout << " ";
        }
        cout << InOrderStore[i] << endl;
    }
    return;
}

void InOrder(TreeNode *tree)
{
    if (tree != NULL)
    {
        InOrder(tree->lchild);
        InOrderStore.push_back(tree->data);
        InOrder(tree->rchlid);
    }
    return;
}

int main()
{
    int Node = -1;
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    while (1)
    {
        scanf("%d", &Node);
        if (Node == 0) break;
        TreeNodeStore.push_back(Node);
    }

    root->data = TreeNodeStore[0];
    root->lchild = NULL;
    root->rchlid = NULL;

    for (int i = 1; i < TreeNodeStore.size(); i++)
    {
        CreateTree(root, TreeNodeStore[i]);
    }

    CalculateTreeNodeBackSpace(root, 0);
    InOrder(root);
    VisualizeTree(root, 0);

    printf("\n");

    for (int i = 0; i < InOrderStore.size(); i++)
    {
        printf(" %d", InOrderStore[i]);
    }
    printf("\n");
    return 0;
}