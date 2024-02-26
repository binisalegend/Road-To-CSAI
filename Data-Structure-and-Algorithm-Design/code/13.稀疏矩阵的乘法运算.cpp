/*
 * @Description: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-16 23:55:19
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-28 21:43:35
 */

#include<bits/stdc++.h>  
#include<algorithm>  
using namespace std;  
#define MAXSIZE 10005      
int row_1 = 0, column_1 = 0, num_1 = 0, row_2 = 0, column_2 = 0, num_2 = 0; // 初始化行列数以及非零元的个数  
int ResultRow = 0, ResultColumn = 0, ResultNum = 0;  // 结果矩阵的参数  
typedef struct   
{  
    int row, column;  
    int value = 0;  
}NotZeroItem;   //非零元素的信息  
  
NotZeroItem *matrix_1, *matrix_2, *matrix_result;   // 矩阵  
      
int ResultMatrixCalculate()  // 结果矩阵运算参数  
{  
    matrix_result[0].value = 0;  
    for (int i = 1; i <= ResultRow; i++)  
    {  
        for (int j = 1; j <= ResultColumn; j++)  
        {  
            int k = 1;  
            while (k <= num_1)  
            {  
                int l = 1;  
                while (l <= num_2)  
                {  
                    if (matrix_2[l].row > matrix_1[k].column)  
                    {  
                        break;  
                    }  
                    if ((matrix_1[k].column == matrix_2[l].row) && (matrix_1[k].row == i && matrix_2[l].column == j))  
                    {  
                        matrix_result[ResultNum].row = i;  
                        matrix_result[ResultNum].column = j;  
                        matrix_result[ResultNum].value += matrix_1[k].value * matrix_2[l].value;  
                    }  
                    l++;  
                }  
                k++;  
            }  
            if (matrix_result[ResultNum].value != 0)  
            {  
                ResultNum++;  
            }  
            matrix_result[ResultNum].value = 0;  
        }  
    }  
    return ResultNum;  
}  
  
bool cmp_1(NotZeroItem a, NotZeroItem b)   //列优先排序  
{  
    if (a.column != b.column)  
    {  
        return a.column < b.column;  
    }  
    else if (a.row != b.row)  
    {  
        return a.row < b.row;  
    }  
}  
  
bool cmp_2(NotZeroItem a, NotZeroItem b) // 行优先排序  
{  
    if (a.row != b.row)  
    {  
        return a.row < b.row;  
    }  
    else if (a.column != b.column)  
    {  
        return a.column < b.column;  
    }  
}  
  
int main()  
{  
    cin >> row_1 >> column_1 >> num_1;  
    ResultRow = row_1;  
    matrix_1 = (NotZeroItem *)malloc((num_1 + 1)* sizeof(NotZeroItem));  
    for (int i = 1; i <= num_1; i++)  
    {  
        cin >> matrix_1[i].row >> matrix_1[i].column >> matrix_1[i].value;  
    }  
      
    cin >> row_2 >> column_2 >> num_2;  
    ResultColumn = column_2;  
    matrix_2 = (NotZeroItem *)malloc((num_2 + 1)* sizeof(NotZeroItem));  
    for (int i = 1; i <= num_2; i++)  
    {  
        cin >> matrix_2[i].row >> matrix_2[i].column >> matrix_2[i].value;  
    }  
  
    sort(matrix_1 + 1, matrix_1 + num_1 + 1, cmp_1);  
    sort(matrix_2 + 1, matrix_2 + num_2 + 1, cmp_2);  
  
    matrix_result = (NotZeroItem *)malloc(MAXSIZE * sizeof(NotZeroItem));  
    ResultNum = ResultMatrixCalculate();  
  
    printf("%d\n%d\n%d\n", ResultRow, ResultColumn, ResultNum);  
    for (int i = 0; i < ResultNum; i++)  
    {  
        printf("%d,%d,%d\n", matrix_result[i].row, matrix_result[i].column, matrix_result[i].value);  
    }  
    system("pause");  
    return 0;  
}  