#include<bits/stdc++.h>
using namespace std;
#define MAX_SIZE 101    

int N, flag = 0;
int location[MAX_SIZE][MAX_SIZE] = {0};
int dy[4] = {1, -1, 0, 0}, dx[4] = {0, 0, 1, -1};
bool LocPath[MAX_SIZE][MAX_SIZE] = {false};
int step[MAX_SIZE][MAX_SIZE] = {0};

typedef struct 
{
    int x;
    int y;
}loc;

int bfs(int x, int y)
{
    loc start, next;
    start.x = x, start.y = y;
    queue<loc> n;
    n.push(start);
    LocPath[start.x][start.y] = true;
    while (!n.empty())
    {
        loc now = n.front();
        n.pop();
        if (now.x == N && now.y == N)
        {
            flag = 1;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            next.x = now.x + dx[i];
            next.y = now.y + dy[i];
            if (next.x < 1 || next.x > N || next.y < 1 || next.y > N || LocPath[next.x][next.y] == true)
            {
                continue;
            }
            if (location[next.x][next.y] != 1)
            {
                LocPath[next.x][next.y] = true;
                step[next.x][next.y] = step[now.x][now.y] + 1;
                n.push(next);
            }
        }
    }
    return step[N][N];
}
    
int main()
{
    cin >> N >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> location[i][j];
        }
    }

    int FinalResult = bfs(1, 1);

    if (flag == 0)
    {
        printf("There is no solution!\n");
    }
    else
    {
        memset(LocPath, false, sizeof(LocPath));
        stack<loc> result;
        loc find_now = {N, N};
        result.push(find_now);
        int Step = FinalResult;

        while (Step != 0)
        {
            if (find_now.x == 1 && find_now.y == 1)
            {
                break;
            }
            for (int i = 0; i < 4; i++)
            {
                loc find_next = {0, 0};
                find_next.x = find_now.x + dx[i];
                find_next.y = find_now.y + dy[i];

                if (find_next.x < 1 || find_next.y < 1 || find_next.x > N || find_next.y > N || LocPath[find_next.x][find_next.y] == true || location[find_next.x][find_next.y] == 1)
                {
                    continue;
                }
                else
                {
                    LocPath[find_next.x][find_next.y] = true;
                    if (step[find_next.x][find_next.y] == Step - 1)
                    {
                        result.push(find_next);
                        Step--; 
                        find_now.x = find_next.x;
                        find_now.y = find_next.y;
                        break;
                    }
                }
            }
        }
        while (!result.empty())
        {
            printf("<%d,%d> ", result.top().x, result.top().y);
            result.pop();
        }
        printf("\n");
    }
    
    system("pause");
    return 0;
}