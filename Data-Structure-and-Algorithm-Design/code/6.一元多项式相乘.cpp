/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int    coef, exp;  
    struct node  *next;  
} NODE;  
  
void multiplication( NODE *, NODE * , NODE * );  
void input( NODE * );  
void output( NODE * );  
  
void input( NODE * head )  
{   int flag, sign, sum, x;  
    char c;  
  
    NODE * p = head;  
  
    while ( (c=getchar()) !='\n' )  
    {  
        if ( c == '<' )  
        {    sum = 0;  
             sign = 1;  
             flag = 1;  
        }  
        else if ( c =='-' )  
            sign = -1;  
        else if( c >='0'&& c <='9' )  
        {    
            sum = sum*10 + c - '0';  
        }  
        else if ( c == ',' )  
        {    
            if ( flag == 1 )  
            {   
                x = sign * sum;  
                sum = 0;  
                flag = 2;  
                sign = 1;  
            }  
        }  
        else if ( c == '>' )  
        {    p->next = ( NODE * ) malloc( sizeof(NODE) );  
             p->next->coef = x;  
             p->next->exp  = sign * sum;  
             p = p->next;  
             p->next = NULL;  
             flag = 0;  
        }  
    }  
}  
  
void output( NODE * head )  
{  
    while ( head->next != NULL )  
    {   head = head->next;  
        printf("<%d,%d>,", head->coef, head->exp );  
    }  
    printf("\n");  
}  
  
int main()  
{   NODE * head1, * head2, * head3;  
  
    head1 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head1 );  
  
    head2 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head2 );  
  
    head3 = ( NODE * ) malloc( sizeof(NODE) );  
    head3->next = NULL;  
    multiplication( head1, head2, head3 );  
  
    output( head3 );  
    system("pause");
    return 0;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  

void multiplication(NODE *head1, NODE *head2, NODE *head3)
{
    NODE *p1, *p2, *p3;
    p1 = p2 = p3 = head3;
    NODE *h1 = head1->next, *h2 = head2->next;
    int coef = 0, exp = 0;
    
    while(h1 != NULL)
    {
        while(h2 != NULL)
        {
            coef = h1->coef * h2->coef;
            if (coef == 0)
            {
                h2 = h2->next;
                continue;
            }

            exp = h1->exp + h2->exp;

            if (p1->next == NULL)
            {
                NODE *s = (NODE*)malloc(sizeof(NODE));
                s->exp = exp;
                s->coef = coef;
                s->next = NULL;

                p1->next = s;
            }
            else
            {
                if(p3->next != NULL && exp > p3->next->exp)
                {
                    p2 = p3;

                    while(p2->next != NULL && exp > p2->next->exp)
                    {
                        p2 = p2->next;
                        p3 = p2;
                    }
                }
                else
                {
                    while(p2->next != NULL && exp > p2->next->exp)
                    {
                        p2 = p2->next;
                        p3 = p2;
                    }
                }

                NODE *temp = p2->next;
                if(p2->next == NULL)
                {
                    NODE *s = (NODE*)malloc(sizeof(NODE));
                    s->exp = exp;
                    s->coef = coef;
                    s->next = NULL;

                    p2->next = s;
                }
                else if(temp->exp == exp)
                {
                    temp->coef += coef;
                    if(temp->coef == 0)
                    {
                        NODE *dele = temp->next;
                        p2->next = dele;
                        free(temp);
                    }
                }
                else if(temp->exp > exp)
                {
                    NODE *s = (NODE*)malloc(sizeof(NODE));
                    s->coef = coef;
                    s->exp = exp;

                    p2->next = s;
                    s->next = temp;
                }
            }
            h2 = h2->next;
            p2 = head3;
        }
        h2 = head2->next;
        h1 = h1->next;
    }

    if(head3->next == NULL)
    {
        NODE *s = (NODE*)malloc(sizeof(NODE));
        s->coef = 0;
        s->exp = 0;
        s->next = NULL;

        head3->next = s;
    }
    return;
}