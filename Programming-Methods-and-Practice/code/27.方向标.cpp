#include<bits/stdc++.h>
using namespace std;

#define MAX 2010
#define ModNumber 2147483647

long long N = 0;
long long point[MAX];
long long dp[MAX][MAX];

long long CalculateSituation(long long N)
{
    long long result = 0;
    dp[1][point[0]] = 1;
    for (long long i = 1; i <= N; i++)
    {
        for (long long j = 0; j <= N+1; j++)
        {
            long long left = min(j, point[i-1]);
            long long right = max(j, point[i-1]);

            if (point[i] <= left)
            {
                dp[i][right] = (dp[i-1][j] + dp[i][right]) % ModNumber;
            }
            else if (point[i] >= right)
            {
                dp[i][left] = (dp[i-1][j] + dp[i][left]) % ModNumber;
            }
            
            else
            {
                dp[i][right] = (dp[i-1][j] + dp[i][right]) % ModNumber;
                dp[i][left] = (dp[i-1][j] + dp[i][left]) % ModNumber; 
            }
        }
    }
    
    for (int i = 0; i <= N+1; i++)
    {
        result = (result + dp[N][i]) % ModNumber;
    }
    return result;
}

int main()
{
    memset(dp, 0, sizeof(dp));
    memset(point, 0, sizeof(point));

    scanf("%lld", &N);
    cin >> point[0];
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &point[i]);
    }

    long long result = CalculateSituation(N);
    cout << result << endl;

    system("pause");
    return 0;
}