//妈的太不容易了沃日，必须来记两笔
//首先先学一下如何用指针定位字符数组中的某个特定元素的strchr函数，然后就可以分开存储整数和小数部分
//基本的运算思路没啥问题，和上一题二进制大体相似
//这题主要恶心在各种奇奇怪怪的保密，比如输入要保留前面的垃圾0，而输出又要去掉，但是只有一个0在小数点前就又要保留
//后来想出判断方式的同时想到了一种就是可以把输出的垃圾0替换成空格，这样输出就一定是三个数据里最长的了
//对齐问题上，由于是小数点对齐，而进位后只可能进位到整数部分，所以小数部分直接按结果的小数部分算；补空格就行
//整数部分取最大长度，根据差值补空格即可
//还要注意两个输入都没有小数点那么结果也没有小数点(并且最后没空格)，如果是一个没有小数点那么另一个数输出要补空格
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    char number1_int[10000] = "", number2_int[10000] = "";
    char number1_fra[10000] = "", number2_fra[10000] = "";
    int flag1 = 0, flag2 = 0;

    char input1[10000];
    scanf("%s", input1);  // 读取整个输入字符串，包括小数点

    char *decimal_point1 = strchr(input1, '.');  // 查找小数点的位置

    if (decimal_point1 != NULL) 
    {
        *decimal_point1 = '\0';  // 将小数点替换为字符串结束符

        strcpy(number1_int, input1);  // 复制整数部分到number1_int
        strcpy(number1_fra, decimal_point1 + 1);  // 复制小数部分到number1_fra
    }
    else
    {
        strcpy(number1_int, input1);
        flag1 = 1;
    }

    char input2[10000];
    scanf("%s", input2);  // 读取整个输入字符串，包括小数点

    char *decimal_point2 = strchr(input2, '.');  // 查找小数点的位置

    if (decimal_point2 != NULL) 
    {
        *decimal_point2 = '\0';  // 将小数点替换为字符串结束符

        strcpy(number2_int, input2);  // 复制整数部分到number2_int
        strcpy(number2_fra, decimal_point2 + 1);  // 复制小数部分到number2_fra
    }
    else
    {
        strcpy(number2_int, input2);
        flag2 = 1;
    }

    int length_int_1 = 0, length_int_2 = 0;
    int length_fra_1 = 0, length_fra_2 = 0;
    length_int_1 = strlen(number1_int);
    length_int_2 = strlen(number2_int);
    length_fra_1 = strlen(number1_fra);
    length_fra_2 = strlen(number2_fra);

    int rem_int_1 = length_int_1;
    int rem_int_2 = length_int_2;
    int rem_fra_1 = length_fra_1;
    int rem_fra_2 = length_fra_2;
    
    char result_int[1002] = "", result_fra[1002] = "";

    int carry_bit = 0;
    //先算小数部分
    while (length_fra_1 - length_fra_2 > 0)
    {
        result_fra[length_fra_1-1] = number1_fra[length_fra_1-1];
        length_fra_1--;
    }
    while (length_fra_2 - length_fra_1 > 0)
    {
        result_fra[length_fra_2-1] = number2_fra[length_fra_2-1];
        length_fra_2--;
    }
    while (length_fra_1 == length_fra_2 && length_fra_1 != 0 && length_fra_2 != 0)
    {
        int loc = number1_fra[length_fra_1-1] - 48 + number2_fra[length_fra_2-1] - 48 + carry_bit;
        carry_bit = loc / 10;
        result_fra[length_fra_1-1] = loc % 10 + 48;
        length_fra_1--;
        length_fra_2--;
    }
    
    //再算整数部分
    int result_intbite = 0;
    while (length_int_1 > 0 && length_int_2 > 0)
    {
        int loc = number1_int[length_int_1-1] - 48 + number2_int[length_int_2-1] - 48 + carry_bit;
        carry_bit = loc / 10;
        result_int[result_intbite] = loc % 10 + 48;
        result_intbite++;
        length_int_1--;
        length_int_2--;
    }
    while (length_int_1 > 0)
    {
        int loc = number1_int[length_int_1-1] - '0' + carry_bit;
        carry_bit = loc / 10;
        result_int[result_intbite] = loc % 10 + '0';
        result_intbite++;
        length_int_1--;
    }
    while (length_int_2 > 0)
    {
        int loc = number2_int[length_int_2-1] - '0' + carry_bit;
        carry_bit = loc / 10;
        result_int[result_intbite] = loc % 10 + '0';
        result_intbite++;
        length_int_2--;
    }  

    if (carry_bit != 0)
    {
        result_int[result_intbite] = carry_bit + 48;
    }
    
    int length_int_result = 0, length_fra_result = 0;
    length_int_result = strlen(result_int);
    length_fra_result = strlen(result_fra);

//删除结果里的垃圾0
    if (result_int[length_int_result-1] == '0')
    {
        for (int search = length_int_result - 1; search >= 0; search--)
        {
            if ((search == 0 && result_int[1] == ' ') || (result_int[0] == '0' && length_int_result == 1))
            {
                break;
            }
            if (result_int[search] == '0' && result_int[search-1] == '0')
            {
                result_int[search] = ' ';
            }  
            else if (result_int[search] == '0' && result_int[search-1] != '0')
            {
                result_int[search] = ' ';
                break;
            }
        }
    }

//第一行 
    for (int i = 0; i < length_int_result + 3 - rem_int_1; i++)
    {
        printf(" ");
    }
    for (int m = 0; m < rem_int_1; m++)
    {
        printf("%c", number1_int[m]);
    }
    if(flag1 == 0)
    {
        printf(".");
        for (int i = 0; i < rem_fra_1; i++)
        {
            printf("%c", number1_fra[i]);
        }
        for (int i = 0; i < length_fra_result - rem_fra_1; i++)
        {
            printf(" ");
        }
        printf("\n");
    }
    else if (flag1 == 1 && flag2 == 1)
    {
        for (int i = 0; i < rem_fra_1; i++)
        {
            printf("%c", number1_fra[i]);
        }
        for (int i = 0; i < length_fra_result - rem_fra_1; i++)
        {
            printf(" ");
        }
        printf("\n");
    }
    else if(flag1 == 1 && flag2 == 0)
    {
        printf(" ");
        for (int i = 0; i < length_fra_result - rem_fra_1; i++)
        {
            printf(" ");
        }
        printf("\n"); 
    } 
    

//第二行
    printf("+");
    for (int i = 0; i < length_int_result + 2 - rem_int_2; i++)
    {
        printf(" ");
    }
    for (int m = 0; m < rem_int_2; m++)
    {
        printf("%c", number2_int[m]);
    }
    if(flag2 == 0)
    {
        printf(".");
        for (int i = 0; i < rem_fra_2; i++)
        {
            printf("%c", number2_fra[i]);
        }
        for (int i = 0; i < length_fra_result - rem_fra_2; i++)
        {
            printf(" ");
        }
        printf("\n");
    }
    else if(flag2 == 1 && flag1 == 0)
    {
        printf(" ");
        for (int i = 0; i < length_fra_result - rem_fra_2; i++)
        {
            printf(" ");
        }
        printf("\n"); 
    }
    else
    {
        for (int i = 0; i < length_fra_result - rem_fra_2; i++)
        {
            printf(" ");
        }
        printf("\n"); 
    }

//第三行狗横线
    for (int i = 0; i < 4 + length_int_result + length_fra_result; i++)
    {
       printf("-"); 
    }
    printf("\n");

//第四行结果
    printf("   ");
    for (int i = length_int_result - 1; i >= 0; i--) 
    {
        printf("%c", result_int[i]);
    }
    if (flag1 == 1 && flag2 == 1)
    {
       printf("\n");
    }
    else
    {
        printf(".");
        puts(result_fra);
    } 
    return 0;
}