/*
 * @Description: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-09-27 22:18:58
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-30 10:36:13
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int n, count = 0, flag = 0;
    scanf("%d", &n);

    // 使用动态内存分配来存储多个字符串
    char **loc = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        loc[i] = (char *)malloc(10 * sizeof(char)); 
        scanf("%s", loc[i]);
    }

    for (int i = 0; i < n; i++)
    {
        if (strlen(loc[i]) > 10)
        {
            for (int j = 0; j < i; j++)
            {
                if (strcmp(loc[i], loc[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                count++;
            }
        }
        flag = 0;
    }
    printf("%d\n", count);
    return 0;
}