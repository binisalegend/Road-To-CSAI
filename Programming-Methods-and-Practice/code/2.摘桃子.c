#include<stdio.h>
int main()
{
   int Tree_num = 0, v = 0, b[100000] = {0}, peach_num[100000] = {0}, Day = 0, day = 0, maxday = 0, Total = 0;
   //在定义b和peach_num数组时需要先把数据存储到数组中再动态分配内存，memset和malloc都不行
   scanf("%d %d", &Tree_num, &v);
   if (Tree_num == 0)
   {
        printf("0\n");
   }
   else
   {
        for (int i = 0; i < Tree_num; i++)   //引入变量
        {
                scanf("%d", &Day);
                scanf("%d", &day);
                if (Day > maxday)
                {
                    maxday = Day;
                }
                b[Day-1] += day;
        }
        if (b[0] < v)   //第一天熟的桃子全部可以摘掉，没剩下
                {
                    peach_num[0] = b[0];
                    b[0] = 0;
                }
            else  //摘不完，剩下的就是b[0]
            {
                peach_num[0] = v;
                b[0] = b[0] - v;
            }
        for (int n = 1; n < maxday; n++)   //开始进行循环计数
        {
            if (b[n] < v && b[n-1] < v)  //两天剩下的桃子都比v少
            {
                if (b[n] + b[n-1] < v) //全摘完没剩下
                {
                    peach_num[n] = b[n] + b[n-1];
                    b[n] = 0;
                }
                else  //剩下的就是两天加起来-v
                {
                    peach_num[n] = v;
                    b[n] = b[n] + b[n-1] - v;
                }     
            }
            else if (b[n] < v && b[n-1] >= v)
            {
                peach_num[n] = v;
            }
            else if (b[n] >= v && b[n-1] < v)
            {
                peach_num[n] = v;
                b[n] = b[n] + b[n-1] - v;
            }
            else if (b[n] >= v && b[n-1] >= v)
            {
                peach_num[n] = v;
                b[n-1] -= v;
            }
        }
        if (b[maxday-1] < v)
        {
                peach_num[maxday] = b[maxday-1];
        }
        else
        {
                peach_num[maxday] = v;
        }
        for (int t = 0; t < maxday + 1; t++)
        {
                Total += peach_num[t];
        }
        printf("%d\n", Total);
   }
   return 0;
}