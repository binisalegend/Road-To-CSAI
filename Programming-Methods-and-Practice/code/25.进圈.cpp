#include<bits/stdc++.h>
using namespace std;

typedef struct 
{
    int x = 0;
    int y = 0;
    int time = 0;
}point;

char loc[1002][1002] = {'/'};
int n, m, k;
bool already[1002][1002] = {{false}};
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int bfs(point start, point end)
{
    point now;
    queue<point> q;
    q.push(start);
    int flag = 0, ans = 0;
    already[start.x][start.y] = true;
    while(!q.empty() && flag == 0)
    {
        now = q.front();
        q.pop();
        for (int i = 0; i < 4 && flag == 0; i++)
        {
            for (int j = 1; j <= k && flag == 0; j++)
            {
                point next;
                next.x = now.x + dx[i] * j;
                next.y = now.y + dy[i] * j;
                if(next.x <= 0 || next.x > n || next.y <= 0 || next.y > m || loc[next.x][next.y] == '#')
                {
                    break;
                }
                if(already[next.x][next.y] == true)
                {
                    continue;
                }
                if(next.x == end.x && next.y == end.y)
                {
                    flag = 1;
                    ans = now.time + 1;
                }
                next.time = now.time + 1;
                q.push(next);
                already[next.x][next.y] = true;
            }
        }
    }
    if(flag == 0)
    {
        return -1;
    }
    else
    {
        return ans;
    }
}

int main()
{
    point start, end;
    
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> loc[i][j];
        }
        getchar();
    }
    cin >> start.x >> start.y >> end.x >> end.y;

    int End = bfs(start, end);
    cout << End << endl;
    system("pause");
    return 0;
}