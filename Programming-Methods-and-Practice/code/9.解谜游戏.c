#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int row = 0, column = 0, min_times = 256;
char tem[17][17], square[17][17];

void change(char *a)   //按下按钮状态变化函数
{
    if (*a == '0')
    {
        *a = '1';
    }
    else
    {
        *a = '0';
    } 
}

void convert(char square[][17], int row_count, int column_count)  //灯光变换函数
{
    change(&square[row_count][column_count]);
    if (column_count > 0)
    {
        change(&square[row_count][column_count-1]);
    }
    if (column_count < column - 1)
    {
        change(&square[row_count][column_count+1]);
    }
    if (row_count > 0)
    {
        change(&square[row_count-1][column_count]);
    }
    if (row_count < row - 1)
    {
        change(&square[row_count+1][column_count]);
    }
}

void Unload()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            tem[i][j] = square[i][j];
        }
    }
}

int TimCalculation()
{
    Unload();
    int loc = 0;
    for (int i = 0; i < row - 1; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (tem[i][j] == '1')
            {
                loc++;
                convert(tem, i + 1, j);
            }
        }
    }
    
    for (int i = 0; i < column; i++)
    {
        if (tem[row-1][i] == '1')
        {
            return -1;
        }
    }
    return loc; 
}

void FirstlineCondition(int count, int loc) 
{
    if (loc == column)
    {
        int judge = TimCalculation();
        if (judge == -1)
        {
            return;
        }
        if (judge + count < min_times)
        {
            min_times = judge + count;
        }
        return;
    }
    
    convert(square, 0, loc);
    FirstlineCondition(count + 1, loc + 1);

    convert(square, 0, loc);
    FirstlineCondition(count, loc + 1);
}

int main()
{
    scanf("%d %d", &row, &column);
    getchar();    //浅浅吃个回车

    // char **square = (char **)malloc((row+1) * sizeof(char *));
    for (int row_count = 0; row_count < row; row_count++)
    {
        // square[row_count] = (char *)malloc((column+1) * sizeof(char));
        for (int column_count = 0; column_count < column; column_count++)
        {
            scanf("%c", &square[row_count][column_count]);
        }
        getchar();  //再浅浅吃一些每行末的回车
    }

    FirstlineCondition(0, 0);
    printf("%d\n", min_times);
    return 0; 
}