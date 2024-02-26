#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct 
{
    long long int a;
    long long int b;
    long long int c;
    long long int number;
}SideLen;

SideLen max_min(SideLen a, SideLen b)
{
    SideLen max_min;
    max_min.a = a.a > b.a ? a.a : b.a;
    max_min.b = a.a > b.a ? a.b : b.b;
    max_min.c = a.a > b.a ? a.c : b.c;
    max_min.number = a.a > b.a ? a.number : b.number;
    return max_min;
}

long long int min(long long int a, long long int b, long long int c)
{
    long long int min;
    if (a < b)
    {
        if (a < c)
        {
            min = a;
        }
        else
        {
            min = c;
        }
    }
    else
    {
        if (b < c)
        {
            min = b;
        }
        else
        {
            min = c;
        }
    }
    return min;
}

long long int max(long long int a, long long int b, long long int c)
{
    long long int max;
    if (a > b)
    {
        if (a > c)
        {
            max = a;
        }
        else
        {
            max = c;
        }
    }
    else
    {
        if (b > c)
        {
            max = b;
        }
        else
        {
            max = c;
        }
    }
    return max;
}

long long int mid(long long int a, long long int b, long long int c)
{
    long long int mid;
    if (a > b)
    {
        if (c > a)
        {
            mid = a;
        }
        else
        {
            if (b > c)
            {
                mid = b;
            }
            else
            {
                mid = c;
            }
        }
    }
    else  //a<b
    {
        if (c < a)
        {
            mid = a;
        }
        else  //a<b c >a
        {
            if (b > c)
            {
                mid = c;
            }
            else
            {
                mid = b;
            }
        }
    }
    return mid;
}

int cmp(const void *a, const void *b)
{
    SideLen *c = (SideLen *)a;
    SideLen *d = (SideLen *)b;
    if (c->c != d->c)
    {
        return d->c - c->c;
    }
    else if (c->b != d->b)
    {
        return d->b - c->b;
    }
    else
    {
        return d->a - c->a;
    }
}

int main()
{
    int n, k = 0;
    long long int max_num1 = 0, max_num2 = 0, x, y, z;
    scanf("%d", &n);

    SideLen *CrystalBall = (SideLen *)malloc((n + 1) * sizeof(SideLen));

    for (int i = 0; i < n; i++)
    {
        scanf("%lld %lld %lld", &x, &y, &z);
        CrystalBall[i].a = min(x, y, z);
        CrystalBall[i].b = mid(x, y, z);
        CrystalBall[i].c = max(x, y, z);
        CrystalBall[i].number = i + 1;
    }
    //验证只有一个水晶球的情况
    SideLen Max = CrystalBall[0];
    for (int i = 1; i < n; i++)
    {
        Max = max_min(CrystalBall[i], Max);
    }
    k = 1;

    //验证水晶球合并的情况
    qsort(CrystalBall, n, sizeof(CrystalBall[0]), cmp);  //将结构数组先按照最长边排序，如果相同再看第二长边，以此类推
    for (int i = 0; i < n - 1; i++)
    {
        if ((CrystalBall[i].c == CrystalBall[i+1].c) && (CrystalBall[i].b == CrystalBall[i+1].b)) //比较最长和第二长边是否相等
        {
            long long int min_loc = min(CrystalBall[i].c, CrystalBall[i].b, (CrystalBall[i].a + CrystalBall[i+1].a));
            if (min_loc > Max.a)
            {
                Max.a = min_loc;
                k = 2;
                max_num1 = CrystalBall[i].number;
                max_num2 = CrystalBall[i+1].number;
            }
        }
    }
    
    if (k == 1)
    {
        printf("1\n%lld\n", Max.number);
    }
    else
    {
        printf("2\n%lld %lld\n", max_num1, max_num2);
    }
    return 0;
}