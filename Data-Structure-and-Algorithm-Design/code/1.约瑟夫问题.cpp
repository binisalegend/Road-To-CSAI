#include<bits/stdc++.h>
using namespace std;
    
int n, k, m, OutCount = 1, loc;    
int *OutputNum;
queue<int> team;


void Calculate()
{
    for (int i = 1; i <= n; i++)
    {
        team.push(i);
    }

    int count = 1;
    while (!team.empty())
    {
        loc = team.front();
        if (count == k)
        {
            while (!team.empty())
            {
                for (int i = 1; i < m; i++)
                {
                    loc = team.front();
                    team.push(loc);
                    team.pop();
                }
                OutputNum[OutCount++] = team.front();
                team.pop();
            }
        }
        else
        {
            team.push(loc);
            team.pop();
            count++;
        }
    }
    
}
    
int main()
{
    scanf("%d,%d,%d", &n, &k, &m);
    OutputNum = (int *)malloc((n + 1) * sizeof(int));

    if (n < 1 || k < 1 || m < 1)    
    {
        printf("n,m,k must bigger than 0.\n");
    }
    else if (k > n)
    {
        printf("k should not bigger than n.\n");
    }
    else
    {
        Calculate();
        for (int i = 1; i <= n; i++)
        {
            if((i % 10 == 0) || (i == n))
            {
                cout << OutputNum[i] << endl;
            }
            else
            {
                cout << OutputNum[i] << " ";
            }
        }
    }
    system("pause");
    return 0;
}