#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#define MAX_NUM 1000005
typedef struct 
{
    int color;
    long long height;
}build;

int *CalculateColorNums(build *building, int n)
{
    int *color_nums = (int *)malloc((n+1) * sizeof(int));
    build *Stacks = (build *)malloc((n+1) * sizeof(build));
    int StackSize = 0, count = 0;
    int *hashSet = (int *)malloc(1000005 * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        //判断颜色是不是重复的
        if (hashSet[building[i].color] == 0)
        {
            count++;
        }

        hashSet[building[i].color] += 1;
        //看不见的楼房出栈
        while (StackSize > 0 && Stacks[StackSize - 1].height < building[i].height)
        {
            if (hashSet[Stacks[StackSize - 1].color] > 0)
            {
                hashSet[Stacks[StackSize - 1].color] -= 1;
                if (hashSet[Stacks[StackSize - 1].color] == 0)
                {
                    count--;
                }
            }
            StackSize -= 1;
        }

        Stacks[StackSize].color = building[i].color;
        Stacks[StackSize].height = building[i].height;

        color_nums[i] = count;
        StackSize++;
    }
    return color_nums;
}

int main()
{
    int trash;
    scanf("%d", &trash);
    for (int i = 0; i < trash; i++)
    {
        int n = 0;
        scanf("%d", &n);
        build *building = (build *)malloc((n+1) * sizeof(build));

        for (int j = 0; j < n; j++)
        {
            scanf("%d", &building[j].color);
        }
        for (int j = 0; j < n; j++)
        {
            scanf("%lld", &building[j].height);
        }
        
        int *result = CalculateColorNums(building, n);
        for (int j = 0; j < n; j++)
        {
            printf("%d", result[j]);
            if (j != n - 1)
            {
                printf(" ");
            }
        }
        printf("\n");

        free(result);
        free(building);
    }
    return 0;
}