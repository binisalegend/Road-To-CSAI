#include<stdio.h>
int main()
{
    int T;
    scanf("%d", &T);
    long long int Length_max;
    for (int times = 0; times < T; times++)
    {
        scanf("%lld", &Length_max);
        int height[100001] = {0};
        for(int Length = 1; Length <= Length_max; Length++)
        {
            scanf("%lld", &height[Length]);
        }
        long long int deep = 0, tot_store = 0, In = 1, Out = Length_max;
        while (In < Out)
        {
            deep = height[Out];
            while (height[In] >= height[Out] && In != Out)
            {
                if (height[Out] <= deep)
                {
                    tot_store += deep - height[Out];
                }
                else
                {
                    deep = height[Out];
                } 
                Out--;
            }

            deep = height[In] ;
            while (height[In] < height[Out] && In != Out)
            {
                if (height[In] <= deep)
                {
                    tot_store += deep - height[In];
                }
                else
                {
                    deep = height[In];
                } 
                In++;
            }
        }
        printf("%lld\n", tot_store); 
    }
    return 0;
}