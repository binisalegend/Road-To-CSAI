/*
 * @Descripttion: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-22 17:59:47
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-22 17:59:51
 */
#include<iostream>  
#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
  
using namespace std;  
  
typedef enum{ATOM,LIST} Elemtype;  
struct GLNode{  
    Elemtype tag;  
    union{  
        char atom;  
        struct{  
            struct GLNode *head,*tail;  
        };  
    };  
};  
typedef struct GLNode GList;  
  
void GetSubstr(char substr[], char headstr[])  
{  
    char s[strlen(substr)];  
    int i = 0;  
    int j = 0;  
    int flag = 0;  //括号的层数  
    int r = 0;  
    while(substr[i] && (substr[i] != ','|| flag))  
    {  
        if(substr[i]=='(') flag++;  //加一层括号  
        else if(substr[i]==')') flag--;         //去掉一层括号  
        if(substr[i]!=','||(substr[i]==','&&flag))  
        {  
            headstr[j]=substr[i];  
            j++;i++;  
        }  
    }  
    headstr[j]='\0';  
    if(substr[i]==',')  //跳过  
    i++;  
    while(substr[i])  
    {  
        s[r]=substr[i];  
        r++;  
        i++;  
    }  
    s[r]='\0';  
    strcpy(substr,s);   //把s的值给substr  
}  
  
GList *GListcreat(char s[])  
{  
    GList *G;  
    GList *p,*q;    //辅助作用  
    int len = strlen(s);  
    char substr[len];   //子字符串  
    char headstr[len];  //存储表头  
    if(len==0||!strcmp(s,"()"))  
    {  
        //输入为空或者表为空的情况  
        G = NULL;  
    }  
    else if(len==1)  
    {            //只有一个原子  
        G = (GList*)malloc(sizeof(GList));  
        if(!G)  
        {  
            exit(0);            //申请内存失败，直接退出程序  
        }  
        G->tag=ATOM;  
        G->atom = *s; //！！！！！！union联合体共用内存地址，操作后会导致tag也空       //   
        // G->head=NULL;//！！！！  
        G->tail=NULL;  
    }  
    else  
    {             
        //有表头也有表尾  
        G = (GList*)malloc(sizeof(GList));  
        if(!G)  
        {  
            exit(0);  
        }  
        G->tag=LIST;  
        p = G;  
        s++;  
        strncpy(substr,s,len-2);  ///去掉最外面的括号（）  
        substr[len-2]='\0'; //手动加上结束符号  
        // 只要子串还有，一直在这个循环  
        while(len>0)  
        {  
            GList *r;  
            GetSubstr(substr,headstr);  
            r = GListcreat(headstr);  //递归建立表头  
            p->head=r;  
            q=p;  
            len = strlen(substr);  
            if(len>0)  
            {  
                p = (GList*)malloc(sizeof(GList));  
                if(!p)  
                {  
                    exit(0);  
                }  
                p->tag=LIST;  
                q->tail=p;  
            }  
        }  
        q=p;    //如果上面的while没有运行的，下一句就会存在使用未初始化的指针的情况  
        q->tail=NULL;  //建立完成后加上结尾  
    }  
    return G;  
}  
  
void GListPrint(GList *G)  
{  
    GList *p,*q;  
    if(G&&!G->tag)  
    {   //不为空而且是原子，这个不需要括号  
        cout << G->atom;  
    }  
    else  
    {  
        cout << '(';  
        while(G)  
        {  
            p=G->head;  
            q=G->tail;  
            if(p&&q&&!p->tag)  
            {    
                //p为原子节点，有后续节点  
                cout<<p->atom<<',';  
                p = q->head;  
                q=q->tail;  
            }  
            if(p!=NULL&&!q&&!p->tag)  
            {     
                //p为原子节点，q为NULL，即G没有表尾  
                cout<<p->atom;  
                G = q;  
            }  
            else  
            {         
                //后续节点  
                if(!p) cout<<"()";  
                else GListPrint(p);  
                if(q)   //有表尾，先打印“，”，  
                cout<<',';  
                G = q;  //表尾给G，只要不为NULL，重复循环  
            }  
        }  
        cout<<')';  
    }  
}  
  
GList *Freelist(GList *G,int n)  
{  
    GList *p;  
    if(n==1)  
    {  
        p=G->head;  
        G->tail = NULL;  
        G = NULL;  
        cout<<"destroy tail"<<endl;  
        cout<<"free list node"<<endl;  
    }else if(n==2)  
    {  
        p = G->tail;  
        G->head = NULL;  
        G=NULL;  
        cout<<"free head node"<<endl;  
        cout<<"free list node"<<endl;  
    }  
    else exit(0);  
    return p;  
}  
  
int main()  
{  
    string assistStr;   //方便接收广义表的字符串  
    int i;    
    char *s;    //用数组存储输入的字符串  
    GList *G;  
    int choose;  
    int strlen;//freopen("file out.txt","r",stdin);  
    cin>>assistStr;//后者得到的结果是无符号整型，进行强制转换，不转换也没事  
    strlen = (signed int) assistStr.size();// 申请内存  
    s = (char *)malloc(sizeof(char)*(strlen+1));  
    for(i=0;i<(signed int)assistStr.size();i++)  
    {  
        s[i]=assistStr[i];  
    }  
    s[strlen]='\0'; //手动加上结束符  
    G = GListcreat(s);  
    cout<<"generic list: ";  
    GListPrint(G);  
    cout<<endl;  
    while(G&&G->tag)  
    {  
        cin>>choose;  
        switch(choose)  
        {  
            // 每一个case是不需要大括号的  
            case 1:  
                G = Freelist(G,1);  
                cout<<"generic list: ";  
                GListPrint(G);  
                cout<<endl;  
                break;      //没有break的话会接着执行下面的case2  
            case 2:  
                G = Freelist(G,2);  
                cout<<"generic list: ";  
                GListPrint(G);  
                cout<<endl;  
                break;  
            default:  
                break;  
        }  
    }  
    system("pause");  
    return 0;  
}