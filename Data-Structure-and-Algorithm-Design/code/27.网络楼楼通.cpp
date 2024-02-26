#include<bits/stdc++.h>
using namespace std;
#define MAXNUM 1010
#define INF 0x3f3f3f3f
    
int BuildingNum = 0, TotalLine = 0;    
int build1, build2, length;
int Line[MAXNUM][MAXNUM];
int min_Line[MAXNUM];
bool visited[MAXNUM] = {false};
long long sum = 0;

long long Prime(int pos)
{
    min_Line[pos] = 0;
    for (int i = 1; i <= BuildingNum; i++)
    {
        int current_len = -1;
        for (int j = 1; j <= BuildingNum; j++)
        {
            if (visited[j] == false && (current_len == -1 || min_Line[j] < min_Line[current_len]))
            {
                current_len = j;
            }
        }

        sum += min_Line[current_len];
        visited[current_len] = true;
        for (int j = 1; j <= BuildingNum; j++)
        {
            if (visited[j] == false)
            {
                min_Line[j] = min(min_Line[j], Line[current_len][j]);
            }
        }
    }
    return sum;
}

int main()
{
    cin >> BuildingNum >> TotalLine;
    memset(Line, 0x3f, sizeof(Line));
    memset(min_Line, 0x3f, sizeof(min_Line));
    while (TotalLine--)
    {
        cin >> build1 >> build2 >> length;
        Line[build1][build2] = min(Line[build2][build1], length);
        Line[build2][build1] = min(Line[build1][build2], length);
    }

    long long value = Prime(1);
    if (value >= INF) cout << -1 << endl;
    else cout << value << endl;
    
    return 0;
}