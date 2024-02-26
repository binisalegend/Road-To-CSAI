#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int cmp(void const *a, void const *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    long long n, cnt = 0, j = 0;
    scanf("%lld", &n);
    getchar();
    char *loc = (char *)malloc((100005) * sizeof(char));
    int *Convert = (int *)malloc((n+1) * sizeof(int));
    int Left[100005] = {0}, Right[100005] = {0};
    for (long long i = 0; i < n; i++)
    {
        scanf("%s", loc);
        long long int len = strlen(loc);
        long long int left = 0, right = 0;
        for (long long t = 0; t < len; t++)
        {
            if (loc[t] == '(')
            {
                left++;
            }
            else
            {
                if (left <= 0)
                {
                    right++;
                }
                else
                {
                    left--;
                }
            }
        }
        if ((left != 0) && (right != 0))
        {
            continue;
        }
        else if (left == 0 && right == 0)
        {
            cnt++;
            continue;
        }
        if (left != 0)
        {
            Left[left] += 1;
        }
        if (right != 0)
        {
            Right[right] += 1;
        }
        j++;
    }
    cnt = cnt / 2;
    
    int i = 1;
    while (j > 1 && i < 100005)
    {
        if (Left[i] != 0 && Right[i] != 0)
        {
            cnt += (Left[i] > Right[i] ? Right[i] : Left[i]);
            j -= (Left[i] + Right[i]);
        }
        i++;
    }
    
    printf("%lld\n", cnt);
    return 0;    
}