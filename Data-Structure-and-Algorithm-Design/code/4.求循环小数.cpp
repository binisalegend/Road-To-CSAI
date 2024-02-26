#include <stdio.h>  
#include <stdlib.h>  
#include<string.h>
  
typedef struct node  
{   
    int data;  
    struct node * next;  
} NODE;  
  
void output( NODE *, int );  
void change( int, int, NODE * );  
  
void output( NODE * head, int kk )  
{   
    int k=0;  
  
    printf("0.");  
    while ( head->next != NULL && k<kk )  
    {
        printf("%d", head->next->data );  
        head = head->next;  
        k++;  
    }  
    printf("\n");  
}  
  
int main()  
{   
    int n, m,k;  
    NODE * head;  
  
    scanf("%d%d%d", &n, &m, &k);  
    head = (NODE *)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
    change( n, m, head );  
    output( head,k );  
    system("pause");
    return 0;  
} 

void change(int n, int m, NODE *head)
{
    int Quotient[10010], Remainder[10010];
    // int *Quotient = (int *)malloc(10010 * sizeof(int));
    // int *Remainder = (int *)malloc(10010 * sizeof(int));
    memset(Quotient, 0, sizeof(Quotient));
    memset(Remainder, 0, sizeof(Remainder));
    int num = n * 10; //去掉整数部分只保留小数部分
    int i = 0, j = 0, p = 0, q = 0, flag = 0;

    for (int i = 0; ; i++)
    {
        Quotient[i] = num / m;
        Remainder[i] = num % m;
        j = 0;
        while (j < i)
        {
            if (Quotient[i] == Quotient[j] && Remainder[i] == Remainder[j])
            {
                p = j;
                q = i;
                flag = 1;
                break;
            }
            j++;
        }
        num = Remainder[i] * 10;

        if (!num) 
        {
            p = i + 1;
            break;
        }
        if (flag == 1)
        {
            break;
        }
    }

    NODE *r = head;
    for (int i = 0; i < p; i++)
    {
        NODE *q = (NODE *)malloc(sizeof(NODE));
        q->data = Quotient[i];
        q->next = NULL;
        r->next = q;
        r = q;
    }
    
    if (flag == 1)
    {
        NODE *r_loc = r;
        for (int i = p; i < q; i++)
        {
            NODE *q = (NODE *)malloc(sizeof(NODE));
            q->data = Quotient[i];
            q->next = NULL;
            r->next = q;
            r = q;
        }
        r->next = r_loc->next;
    }
}