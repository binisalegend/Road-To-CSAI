#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int BlockJudgement(long long *height, long long n, long long max)
{
    int *Stacks = (int *)malloc((n+1) * sizeof(int));
    long long StackSize = 0;
    int flag = 0;

    for (int i = 0; i < n; i++)
    {
        if (StackSize > 0 && Stacks[StackSize-1] == height[i])
        {
            if (StackSize > 1 && Stacks[StackSize-2] < height[i])
            {
                flag = 1;
            }
            StackSize--;
            continue;
        }
        
        Stacks[StackSize] = height[i];
        StackSize++;
    }

    if ((StackSize == 0 || (StackSize == 1 && Stacks[0] == max)) && flag == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    int n;
    while (scanf("%lld", &n) != EOF)
    {
        long long max = 0;
        
        long long *height = (long long *)malloc((n+1) * sizeof(long long));
        for (int i = 0; i < n; i++)
        {
            scanf("%lld", height + i);
        }
        for (int i = 0; i < n; i++)
        {
            if (height[i] > max)
            {
                max = height[i];
            }
        }
        int result = BlockJudgement(height, n, max);
        // printf("%d\n",result);
        if (result == 0)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}