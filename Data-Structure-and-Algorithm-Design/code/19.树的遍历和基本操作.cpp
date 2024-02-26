/*
 * @Descripttion: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-22 17:09:01
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-23 10:51:23
 */
#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 1000000

typedef struct treenode
{
    char data;
    struct treenode *firstchild = NULL, *nextsibling = NULL; 
}TreeNode;

char *str; 
int degree = 0, calc = 0;
    
/**
 * @name: CreateTree
 * @msg: initialate the tree struct
 * @return {*}
 */
TreeNode *CreateTree()
{
    
}

/**
 * @name: VisualizeTree
 * @msg: output the tree's hierarchy structure
 * @param {TreeNode} *tree
 * @param {int} n
 * @return {*}
 */
void VisualizeTree(TreeNode *tree, int n)
{
    int num = n;
    if (tree != NULL)
    {
        for (int i = 0; i < num; i++) 
        {
            cout << ' ';
        }
        cout << tree->data << endl;

        if (tree->firstchild != NULL)
        {
            VisualizeTree(tree->firstchild, n + 4);
        }
        else
        {
            VisualizeTree(tree->nextsibling, n);
        }
    }
    return;
}

/**
 * @name: NodeDegree
 * @msg: Calculate the degree of every node
 * @param {TreeNode} *tree
 * @return {*}
 */
int NodeDegree(TreeNode *tree)
{
    int num = 1;
    if (tree == NULL || tree->firstchild == NULL)
    {
        return 0;
    }
    else 
    {
        TreeNode *temp = tree->firstchild;
        while (temp->nextsibling != NULL)
        {
            num++;
            temp = temp->nextsibling;
        }
    }
    return num;
}

/**
 * @name: TreeDegree
 * @msg: Calculate the degree of the tree
 * @param {TreeNode} *tree
 * @return {*}
 */
int TreeDegree(TreeNode *tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    int count = NodeDegree(tree);
    degree = degree > count ? degree : count;

    if (tree->firstchild != NULL)
    {
        count = NodeDegree(tree->firstchild);
        degree = degree > count ? degree : count;
    }
    if (tree->nextsibling != NULL)
    {
        count = NodeDegree(tree->nextsibling);
        degree = degree > count ? degree : count;
    }
    return degree;
}

int CountDegree(TreeNode *tree, int n)
{
    if (tree == NULL)
    {
        return 0;
    }
    int count = NodeDegree(tree);
    if (count == n)
    {
        calc++;
    }

    if (tree->firstchild != NULL)
    {
        count = NodeDegree(tree->firstchild);
        if (count == n)
        {
            calc++;
        }
    }
    if (tree->nextsibling != NULL)
    {
        count = NodeDegree(tree->nextsibling);
        if (count == n)
        {
            calc++;
        }
    }
    return calc;
}

int main()
{
    str = (char *)malloc(MAXSIZE * sizeof(char));
    cin >> str;

    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root = CreateTree();

    VisualizeTree(root, 0);

    degree = TreeDegree(root);
    cout << "Degree of tree: " << degree << endl;

    for (int i = 0; i <= degree; i++)
    {
        printf("Number of nodes of degree %d: %d\n", i, CountDegree(root, i));
        calc = 0;
    }

    system("pause");
    return 0;
}

// 这题我不好评价emmm，我最后也没想出来怎么能建立这个CreateTree函数，甚至其他的都写好了唉，最后就直接输出不用结构了，代码如下：
// #include<stdio.h>  
  
// int main(){  
//     char c,ab[100];  
//     int num=0,level[100],degree[100]={0},p[100]={0}; //字母数量,每个字母的级别,每个字母的度,每个度的字母数量   
//     int depth=-1,i,j,max=0;  
//     while(1)  
//     {  
//         c=getchar();  
//         if(c=='\n') break;  
//         switch(c)  
//         {  
//             case '(': depth++; break;     
//             case ')': depth--; break;  
//             case ',': break;  
//             default:  
//             num++;  
//             ab[num]=c;  
//             level[num]=depth;  
//             //printf("%c\n",ab[num]);  
//             break;   
//         }  
//     }  
      
//     for(i=1;i<=num;i++)  
//     {  
//         for(j=0;j<level[i];j++)  printf("    ");  
//         printf("%c\n",ab[i]);  
//     }  
//     for(i=1;i<=num;i++)  
//     {  
//         for(j=i+1;j<=num;j++)  
//         {  
//             if(level[j]==level[i]) break;  
//             if(level[j]==level[i]+1) degree[i]++;  
//         }  
          
//     }  
//     for(i=1;i<=num;i++)  
//     {  
//         if(degree[i]>max) max=degree[i];  
//     }  
//     for(i=1;i<=num;i++) p[degree[i]]++;  
//     printf("Degree of tree: %d\n",max);  
//     for(i=0;i<=max;i++)  printf("Number of nodes of degree %d: %d\n",i,p[i]);  
//     return 0;  
// }  