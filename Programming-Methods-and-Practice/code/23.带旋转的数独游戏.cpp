#include<bits/stdc++.h>
using namespace std;

int T;
int Map[18][18] = {0};   //原数独各元素储存数组
int Part_Map[5][5][5] = {0};  //4X4数独各边长储存数组
int turn_cnt[5][5] = {0};    //记录运行当前每个4X4数独旋转了几次
int FinalTurn_cnt[4][4] = {0};  //记录最后每个位置一共运行了几次
int total_turn = 50;         //记录最后运行的次数

//将字符转化成数字方便判定是否符合要求，ABCDEFG跟在9后面以此类推
int convert(char ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return ch - 48;
    }
    else
    {
        return ch - 55;
    }
}

bool check()         //检验每列是否符合要求
{
    for (int j = 1; j <= 4; j++)
    {
        int check1 = 0, check2 = 0, k, l;
        for (int i = 1; i <= 4; i++)
        {
            switch (turn_cnt[i][j])  //根据旋转次数判断哪条边位于一列上
            {
                case 0:
                    k = 4, l = 2;
                    break;
                case 1:
                    k = 1, l = 3;
                    break;
                case 2:
                    k = 2, l = 4;
                    break;
                case 3:
                    k = 3, l = 1;
                    break;
            }
            check1 += Part_Map[i][j][k];
            check2 += Part_Map[i][j][l];
        }
        if((check1 != 120) || (check2 != 120))
        {
            return false;
        }
    }
    return true;
}

void dfs(int count, int row_num, int turn_num)   //三个参数分别为4X4数独的编号、每一行加起来的数值、当前总共旋转的次数
{
    if(count == 17)   //递归结束条件，即16个4X4数独全部遍历完成
    {                                                     
        if (check() && (total_turn > turn_num))          //检验是否满足数独条件，并且更新最小旋转次数
        {
            // memcpy(FinalTurn_cnt, turn_cnt, sizeof(turn_cnt));
            for (int i = 1; i <= 4; i++)
			{
				for (int j = 1; j <= 4; j++)
				{
					FinalTurn_cnt[i][j] = turn_cnt[i][j];
				}
			}
            total_turn = turn_num;
        } 
        return;
    }

    int row, column;              //记录当前4X4数独所在行列
    if (count % 4 == 0)
    {
        row = count / 4;
        column = 4;
    }
    else
    {
        row = count / 4 + 1;
        column = count % 4;
    }

    for (int i = 0; i < 4; i++)      //遍历转0.1.2.3四种旋转情况
    {
        turn_cnt[row][column] = i;   //记录当前4X4数独旋转次数
        row_num += Part_Map[row][column][i+1];
        if (column == 4)             //查看是否到了当前行最后一个4X4数独
        {
            if (row_num == 120)
            {
                dfs(count+1, 0, turn_num + i);    //是最后一个，转到下一行，该行总数清空
            }
        }
        else
        {
            dfs(count+1, row_num, turn_num + i);   //不是该行最后一个数独，下一个数独继续加
        }
        row_num -= Part_Map[row][column][i+1];       //重置当前进行的旋转
    }
}

int main()
{
    cin >> T;
    getchar();
    while (T--)
    {
        total_turn = 50;
        memset(Map, 0, sizeof(Map));
        memset(Part_Map, 0, sizeof(Part_Map));
        memset(turn_cnt, 0, sizeof(turn_cnt));
        memset(FinalTurn_cnt, 0, sizeof(FinalTurn_cnt));
        char tmp;

        for (int i = 1; i <= 16; i++)
        {
            for (int j = 1; j <= 16; j++)
            {
                cin >> tmp;
                Map[i][j] = convert(tmp);
            }
            getchar();
        }

        //将16X16数独分成16个4X4的数独，分别记录小数独每条边的长度
        for (int i = 1; i <= 4; i++)
        {
            for (int j = 1; j <= 4; j++)
            {
                Part_Map[i][j][1] = Map[4*i-3][4*j-3] + Map[4*i-3][4*j-2] + Map[4*i-3][4*j-1] + Map[4*i-3][4*j];
                Part_Map[i][j][2] = Map[4*i-3][4*j] + Map[4*i-2][4*j] + Map[4*i-1][4*j] + Map[4*i][4*j];
                Part_Map[i][j][3] = Map[4*i][4*j-3] + Map[4*i][4*j-2] + Map[4*i][4*j-1] + Map[4*i][4*j];
                Part_Map[i][j][4] = Map[4*i-3][4*j-3] + Map[4*i-2][4*j-3] + Map[4*i-1][4*j-3] + Map[4*i][4*j-3];
            }
        }
        dfs(1, 0, 0);   //从第一个4X4数独开始遍历所有，此时第一行总数为0，旋转次数为0

        printf("%d\n", total_turn);

        //遍历每一个4X4数独，旋转了几次就输出几次数独对应编号
        for (int i = 1; i <= 4; i++)
        {
            for (int j = 1; j <= 4; j++)
            {
                while (FinalTurn_cnt[i][j]--)
                {
                    printf("%d %d\n", i, j);
                }
            }
        }
    }
    system("pause");
    return 0;
}