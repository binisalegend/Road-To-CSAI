// //这种方法本来想用转化为十进制加法后再换回二进制，但是2e100000确实有点太大了
// //最后结果就是只能过第一个示例emmmm(真感觉挺荒谬的难道剩下的示例都是几万几万个数字么我不李姐)
// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>
// #include<math.h>
// int main()
// {
//     int T;
//     scanf("%d", &T);
//     for (int times = 0; times < T; times++)
//     {
//         char result[100009] = "";
//         char number1[100005] ="", number2[100005] = "";
//         long long int length1, length2;
//         scanf("%s %s", number1, number2);
//         length1 = strlen(number1);
//         length2 = strlen(number2); 
//         long long int rem_len1 = length1, rem_len2 = length2;
                
//         long long int decimal1 = 0, decimal2 = 0, decimal_result = 0;
//         for (long long int i = 0; number1[i] != '\0'; i++)
//         {
//             decimal1 +=  pow(2, length1 - 1) * (number1[i] - '0');
//             length1--;
//         }
//         for (long long int j = 0; number2[j] != '\0'; j++)
//         {
//             decimal2 += pow(2, length2 - 1) * (number2[j] - '0');
//             length2--;
//         }
//         decimal_result = decimal1 + decimal2;
//         int count = 0;
//         while (decimal_result)
//         {
//             if (decimal_result % 2 == 1)
//             {
//                 result[count] = '1';
//             }
//             else
//             {
//                 result[count] = '0';
//             }
//             decimal_result /= 2;
//             count++;
//         }
//         long long int length_result;
//         length_result = strlen(result);
//         count -= 1; 
//         for (int p = 0; p < length_result - rem_len1 + 2; p++)
//         {
//             printf(" ");
//         }
//         puts(number1);
//         printf("+");
//         for (int q = 0; q < length_result - rem_len2 + 1; q++)
//         {
//             printf(" ");
//         }
//         puts(number2); 
//         for (int n = 0; n < length_result + 2; n++)
//         {
//             printf("-");
//         }
//         printf("\n");
//         printf("  ");
//         for (int m = length_result - 1; m >= 0 ; m--)
//         {
//             printf("%c", result[m]);
//         }
//         printf("\n") ;
//     }
//     return 0;
// }


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int main()
{
    int T;
    scanf("%d", &T);
    for (int times = 0; times < T; times++)
    {
        char result[100010] = "";
        char number1[100005] ="", number2[100005] = "";
        int length1, length2, carry_bit = 0, result_bite = 0;
        scanf("%s %s", number1, number2);
        length1 = strlen(number1) - 1;
        length2 = strlen(number2) - 1; 
        int rem_len1 = length1 + 1, rem_len2 = length2 + 1;
        
        while (length1 >= 0 && length2 >= 0)
        {
            int loc = 0;
            loc = number1[length1] - 96 + number2[length2] + carry_bit;
            carry_bit = loc / 2;
            result[result_bite] = loc % 2 + '0';
            result_bite++;
            length1--;
            length2--;
        }
        while (length1 >= 0)
        {
            int loc = number1[length1] - '0' + carry_bit;
            carry_bit = loc / 2;
            result[result_bite] = loc % 2 + '0';
            result_bite++;
            length1--;
        }
        while (length2 >= 0)
        {
            int loc = number2[length2] - '0' + carry_bit;
            carry_bit = loc / 2;
            result[result_bite] = loc % 2 + '0';
            result_bite++;
            length2--;
        } 

        if (carry_bit == 1)
        {
            result[result_bite] = '1';
        }
           
        long long int length_result;
        length_result = strlen(result);
        for (int p = 0; p < length_result - rem_len1 + 2; p++)
        {
            printf(" ");
        }
        puts(number1);
        printf("+");
        for (int q = 0; q < length_result - rem_len2 + 1; q++)
        {
            printf(" ");
        }
        puts(number2); 
        for (int n = 0; n < length_result + 2; n++)
        {
            printf("-");
        }
        printf("\n");
        printf("  ");
        for (int m = length_result - 1; m >= 0 ; m--)
        {
            printf("%c", result[m]);
        }
        printf("\n") ;
    }
    return 0;
}