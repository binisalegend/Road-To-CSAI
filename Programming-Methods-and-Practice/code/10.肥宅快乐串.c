#include <stdio.h>
#include <string.h>
#include<stdlib.h>

char character[1010] = "", standard[] = "fattyhappy", trash;

void swap(int num1, int num2, char *tem)
{
    char swap_help; 
    swap_help = tem[num1];
    tem[num1] = tem[num2];
    tem[num2] = swap_help;
}

int find_swaps(char *s) {
    char *target_substring = "fattyhappy";
    int target_length = strlen(target_substring);
    int length = strlen(s);
    
    for (int i = 0; i <= length - target_length; i++) 
    {
        if (strncmp(s + i, target_substring, target_length) == 0) 
        {
            // 找到了 "fattyhappy" 子串，交换它的两个字符即可
            return i + 4; // 返回两个字符中的第一个
        }
    }
    
    return -1;  // 如果没有方案，返回 -1
}

int main()
{
    int T;
    scanf("%d\n", &T);
    for (int Times = 0; Times < T; Times++)
    {
        int swap_num1 = 0, swap_num2 = 0, swap_num3 = 0, rem_help = 0, flag = 0;
        scanf("%s", character);
        trash = getchar();

        if (strlen(character) < 10)
        {
            printf("-1\n");
            goto end3;
        }
        

        //先找有没有直接一样的，换一下t 
        int check = find_swaps(character);
        if (check != -1)
        {
            printf("%d %d\n", check - 1, check);
            goto end3;
        }
        
        //以十个字母为单位遍历整个字符串,判断每十个字符和fattyhappy有几个字母不一样
        for (int i = 0; i <= strlen(character) - 10; i++)
        {
            int diff = 0;
            for (int j = 0; j < 10; j++)
            {
               if (character[i + j] != standard[j])
               {
                    diff++;
                    rem_help = j + i + 1;
                    if (diff > 2)
                    {
                        goto end1;
                    }
               }
            }
            //临时储存数组
            char *tem = (char *)malloc(11 * sizeof(char));
            for (int t = 0; t < 10; t++)
            {
                tem[t] = character[i + t];
            }
            // puts(tem);
            
            if (diff == 2)
            {
                for(int m = 0; m < 10; m++)
                {
                    for (int n = m + 1; n < 10; n++)
                    {
                        swap(m, n, tem); 
                        if (strcmp(tem, standard) == 0) 
                        { 
                            swap_num1 = i+1+m; 
                            swap_num2 = i+1+n; 
                            flag = 1; 
                        } 
                        swap(m, n, tem);
                        if (flag == 1)
                        {
                            goto end2;
                        }
                    }
                }
            }
            
            else if (diff == 1)
            {
               for (int q = i + 10; q < strlen(character); q++)
               {
                    // printf("%c\n", character[q]);
                    if (character[q] == standard[rem_help - i - 1])
                    {
                        swap_num3 = q + 1;
                        flag = 2;
                        goto end2;
                    }
               }
               for (int p = 0; p < i; p++)
               {
                    if (character[p] == standard[rem_help - i - 1])
                    {
                        swap_num3 = p + 1;
                        flag = 2;
                        goto end2;
                    }
               }
            }
            end1:;    
        }
        end2:;
        // printf("%d\n", flag);
        if (flag == 1)
        {
            printf("%d %d\n", swap_num1, swap_num2);
        }
        else if (flag == 2)
        {
            printf("%d %d\n", rem_help, swap_num3);
        }
        else
        {
            printf("-1\n");
        } 
        end3:;
    }
    return 0;
}