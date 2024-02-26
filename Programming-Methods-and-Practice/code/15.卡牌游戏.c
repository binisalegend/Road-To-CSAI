#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int main()
{
    int n = 0, flag = 0, check = 0;
    scanf("%d", &n);
    int *HandCard = (int *)malloc((n+1) * sizeof(int));
    int *Deck = (int *)malloc((n+1) * sizeof(int));
    int *Expect = (int *)malloc((n+1) * sizeof(int));
    int *find_loc= (int *)malloc((n+1) * sizeof(int));
    
    for (int i = 0; i < n; i++)
    {
        scanf("%d", HandCard + i);
        if (HandCard[i] == 1)
        {
            flag = 1;
        }
        if (HandCard[i] != 0)
        {
            find_loc[HandCard[i]] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", Deck + i);
        if (Deck[i] != 0)
        {
            find_loc[Deck[i]] = i + 1;
        }
    }
    
    //1在手牌中
    if (flag == 1)
    {   
        int max_dis = 0;
        for (int i = 1; i < n; i++)
        {
            int dis = find_loc[i + 1] - i;
            if (dis > 0 && dis > max_dis)
            {
                max_dis = dis;
            }
        }
        printf("%d\n", max_dis + n);
    }
    else  //1在牌堆中
    {
        //判断每位置上的期待值(准确说是期待每个数字在哪个位置)
        int j = 1;
        for (int i = 1; i < n; i++)
        {
            Expect[1] = find_loc[1];
            if (i < n + 1 - find_loc[1])
            {
                Expect[i + 1] = find_loc[1] + i;
            }
            else
            {
                Expect[i + 1] = j;
                j = j + 1;
            }
        }           
        // printf("%d %d %d\n", Expect[2], Expect[3], Expect[4]);
        //判断1以后的数字是否构成公差为1的等差数列
        int tem = Deck[n-1];  //2
        for (int i = n - 1; Deck[i] > 1; i--)
        {
            if (Deck[i-1] != tem - 1)
            {
                check = 1;
                break;
            }
            else
            {
                tem -= 1;
            }
        }

        //1以后的数字符合条件
        if (check == 0)
        {
            for (int i = Deck[n-1] + 1; i <= n; i++)
            {
                // printf("%d %d\n", find_loc[i], Expect[i]);
                if (find_loc[i] >= Expect[i])
                {
                    printf("%d\n", find_loc[1] + n);
                    goto end;
                }
            }

            //1前面的数字都在期待位置之前
            // printf("666");
            printf("%d\n", n - Deck[n-1]);
        }
        else
        {
            int max_dis = 0;
            for (int i = n + 1 - find_loc[1]; i > 1; i--)
            {
                if (find_loc[i] > Expect[i])
                {
                    check = 0;
                    int dis = find_loc[i] - Expect[i];
                    max_dis = dis > max_dis ? dis : max_dis;
                }
            }
            if (check == 1)
            {
                printf("%d\n", find_loc[1] + n);
            }
            else
            {
                printf("%d\n", find_loc[1] + max_dis + n);
            }
        }
    }
    end:;
    return 0;
}