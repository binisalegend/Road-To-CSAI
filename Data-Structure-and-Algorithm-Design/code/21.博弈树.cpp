/*
 * @Description: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-28 19:33:32
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-29 00:18:07
 */
#include<bits/stdc++.h>
using namespace std;
    
typedef struct treenode // 定义树节点
{
    char data;
    int status;
    struct treenode *firstchild = NULL, *nextsibling = NULL; 
}*Tree;  
  
typedef enum{ATOM, LIST} Elemtype;  // 定义广义表节点
typedef struct GLNode
{
    Elemtype tag;  
    union{  
        char data;  
        struct{  
            struct GLNode *hp, *tp;  
        }ptr;  
    };  
}*Glist;

void sever(string &str, string &hstr)
{
    int i, k = 0;
    int n = str.length();

    char ch = '\0';
    for(i = 0; i < n && (ch != ',' || k != 0); i++) 
    {
        ch = str[i];
        if(ch == '(') {
            k++;
        }
        if(ch == ')') {
            k--;
        }
    }
    if(i < n) 
    {
        hstr = str.substr(0, i - 1);
        str = str.substr(i, n - i);
    }
    else {
        hstr = str;
        str.clear();
    }
}

void CreateGlist(Glist &L, string s)
{
    if (s == "()")
    {
        L = NULL;
        return;
    }

    L = (Glist)malloc(sizeof(GLNode));
    if (s.length() == 1)
    {
        L->tag = ATOM;
        L->data = s[0];
    }
    else
    {
        L->tag = LIST;

        string sub = s.substr(1, s.length() - 2);
        string hsub;
        Glist p, q;
        p = L;

        while (!sub.empty())
        {
            sever(sub, hsub);
            CreateGlist(p->ptr.hp, hsub);
            q = p;
            if (!sub.empty())
            {
                p = (Glist)malloc(sizeof(GLNode));
                p->tag = LIST;
                q->ptr.tp = p;
            }
        }
        q->ptr.tp = NULL;
    }
}

Glist GetHead(Glist L)
{
    if (L)
    {
        return L->ptr.hp;
    }
    return NULL;
}

Glist GetTail(Glist L)
{
    if (L)
    {
        return L->ptr.tp;
    }
    return NULL;
}

void CreateTree(Tree &T, Glist L)
{
    if (L)
    {
        T = (Tree)malloc(sizeof(treenode));
        T->data = GetHead(L)->data;
        T->firstchild = NULL;
        T->nextsibling = NULL;

        if (GetTail(L))
        {
            Glist h = GetHead(GetTail(L));
            Glist t = GetTail(GetTail(L));
            CreateTree(T->firstchild, h);

            treenode *p = T->firstchild;
            while (t)
            {
                h = GetHead(t);
                t = GetTail(t);
                CreateTree(p->nextsibling, h);
                p = p->nextsibling;
            }
            p->nextsibling = NULL;
        }
    }
    else T = NULL;
    return;
}

int main()
{
    string str;
    cin >> str;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'z')
        {
            printf("%c\n", str[i]);
        }
    }

    Glist L;
    CreateGlist(L, str);

    Tree T;
    CreateTree(T, L);
    
    system("pause");
    return 0;
}