#include<bits/stdc++.h>
using namespace std;
    
int SideLen = 0, NumQueen = 0;  // 棋盘边长，皇后数量
int NumOfMethod = 0; // 记录可行方案数量   
bool *column = NULL, *row = NULL, *L_R_slash = NULL, *R_L_slash = NULL;
    
bool MapCovered() // 判断皇后是否控制了整个棋盘
{
    for (int i = 1; i <= SideLen; i++)
    {
        if (column[i] == false)
        {
            for (int j = 1; j <= SideLen; j++)
            {
                if (row[j] == false && L_R_slash[SideLen + i - j + 1] == false && R_L_slash[i + j] == false)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void traceBack(bool flag, int level, int num)
{
    if (level > SideLen)
    {
        if (num != NumQueen) return;
        if (MapCovered()) NumOfMethod++;
        return;
    }

    // 如果棋盘剩余行放满也无法达成要求皇后数，直接剪枝
    if (SideLen - level + num < NumQueen) return;

    if (!flag)
    {
        traceBack(false, level + 1, num);
        traceBack(true, level + 1, num + 1);
    }
    else
    {
        for (int i = 1; i <= SideLen; i++)
        {
            if (column[i] == false && L_R_slash[SideLen + i - level + 1] == false && R_L_slash[i + level] == false)            
            {
                row[level] = true;
                column[i] = true;
                L_R_slash[SideLen + i - level + 1] = true;
                R_L_slash[i + level] = true;

                traceBack(false, level + 1, num);
                traceBack(true, level + 1, num + 1);

                row[level] = false;
                column[i] = false;
                L_R_slash[SideLen + i - level + 1] = false;
                R_L_slash[i + level] = false;
            }
        }
    }
}


int main()
{
    cin >> SideLen >> NumQueen;

    // 初始化数组
    column = new bool[SideLen + 1];
    row = new bool[SideLen + 1];
    L_R_slash = new bool[2 * SideLen + 1];
    R_L_slash = new bool[2 * SideLen + 1];

    // 初始化数组
    memset(column, false, sizeof(bool) * (SideLen + 1));
    memset(row, false, sizeof(bool) * (SideLen + 1));
    memset(L_R_slash, false, sizeof(bool) * (2 * SideLen + 1)); 
    memset(R_L_slash, false, sizeof(bool) * (2 * SideLen + 1));

    // 调用回溯法
    traceBack(false, 1, 0);
    traceBack(true, 1, 1);

    // 输出
    cout << NumOfMethod << endl;
    return 0;
}