/*
 * @Descripttion: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-22 13:51:07
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-22 15:02:09
 */

#include<bits/stdc++.h>
using namespace std;
    
long long num = 0;
void Calculate(long long nodenum, long long level)    
{
    if (nodenum <= level)
    {
        return;
    }
    else if (nodenum == level + 1)
    {
        num++;
        return;
    }
    else
    {
        nodenum = nodenum - level - 1;
        num++;
        long long LevelNow = 1;

        if (nodenum == 0 || LevelNow > level)
        {
            return;
        }

        long long NumToFull = pow(2, LevelNow) - 1;
        while (nodenum > NumToFull)
        {
            num += pow(2, LevelNow-1);
            LevelNow++;
            nodenum -= NumToFull;
            NumToFull = pow(2, LevelNow) - 1;
            if (LevelNow > level)
            {
                return;
            }
        }
        if (nodenum == NumToFull)
        {
            num += pow(2, LevelNow-1);
            return;
        }
        else 
        {
            Calculate(nodenum, LevelNow-1);
        }
    }
}
    
int main()
{
    long long N = 0;
    cin >> N;
    while (N--)
    {
        num = 0;
        long long NodeNum = 0, Level = 0;
        cin >> NodeNum >> Level;

        Calculate(NodeNum, Level);

        cout << num << endl;
    }
    
    system("pause");
    return 0;
}