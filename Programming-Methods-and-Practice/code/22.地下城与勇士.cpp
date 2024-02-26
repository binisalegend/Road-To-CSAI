#include<bits/stdc++.h>
using namespace std;

typedef struct 
{
    int x;
    int y;
    int time = 0;
}point;

char loc[102][102] = {'/'};
int T, n, m, k;
bool already[102][102][51] = {false};
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int bfs(point start, point end)
{
    int dis = -1;
    point now, next;
    queue<point> q;
    q.push(start);
    already[start.x][start.y][start.time % k] = true;
    while(q.empty() != true)
    {
        now = q.front();
        q.pop();
        if(now.x == end.x && now.y == end.y)
        {
            dis = now.time;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            next.x = now.x + dx[i], next.y = now.y + dy[i], next.time = now.time + 1;
            if(next.x > 0 && next.x <= n && next.y > 0 && next.y <= m && loc[next.x][next.y] != '#' && already[next.x][next.y][next.time % k] == false && loc[next.x][next.y] != '/')
            {
                if(loc[next.x][next.y] == '*')
                {
                    if(next.time % k == 0)
                    {
                        q.push(next);
                        already[next.x][next.y][next.time % k] = true;
                    }
                }
                else
                {
                    q.push(next);
                    already[next.x][next.y][next.time % k] = true;;
                }
            }
        }
    }
    return dis;
}

int main()
{
    point start, end;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> loc[i][j];
                if(loc[i][j] == 'S')
                {
                    start.x = i;
                    start.y = j;
                    start.time = 0;
                }
                else if(loc[i][j] == 'E')
                {
                    end.x = i;
                    end.y = j;
                }
            }
            getchar();
        }
        int End = bfs(start, end);
        cout << End << endl;
        memset(already, false, sizeof(already));
        memset(loc, 0, sizeof(loc));
    }
    system("pause");
    return 0;
}