#include<bits/stdc++.h>
using namespace std;
#define MAX 110


int n = 0, q = 0, MaxWeight = 0, MinMaturity = 0;
int w[MAX], v[MAX], g[MAX];
long long dp[510][510];

void MaxCountCalculate()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 500; j >= 0; j--)   //遍历所有可能的重量
        {
            for (int k = 500; k >= 0; k--) //遍历所有可能的成熟度
            {
                if (dp[j][k] >= 0)
                {
                    if (j + w[i] <= 500)
                    {
                        dp[j+w[i]][min(k+v[i], 500)] = max(dp[j][k] + g[i], dp[j+w[i]][min(k+v[i], 500)]);
                    }
                }
            }
        }
    }
}

long long ResultOutput(int w, int v)
{
    long long result = -1;
    for (int i = 0; i <= w; i++)
    {
        for (int j = v; j <= 500; j++)
        {
            result = max(result, dp[i][j]);
        }
    }
    return result;
}

int main()
{
    memset(dp, -1, sizeof(dp));
    memset(w, 0, sizeof(w));
    memset(v, 0, sizeof(v));
    memset(g, 0, sizeof(g));

    dp[0][0] = 0;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i] >> v[i] >> g[i];
    }
    
    MaxCountCalculate();

    for (int i = 1; i <= q; i++)
    {
        cin >> MaxWeight >> MinMaturity;
        cout << ResultOutput(MaxWeight, MinMaturity) << endl;
    }
    
    system("pause");
    return 0;
}