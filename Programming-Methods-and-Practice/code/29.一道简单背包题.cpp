#include<bits/stdc++.h>
#include<stdbool.h>
using namespace std;
#define MAX 10000000
#define N 2010

int n, V;
long long p[2010] = {0};
long long sum = 0;
long long MethodCount[N][N];

long long CalculateTotalMethods(int n, int V)
{
    MethodCount[0][0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < V; j++)
        {
            MethodCount[i][j] = MethodCount[i-1][j];
        }
        for (int j = 0; j < V; j++)
        {
            int k = (j + p[i] % V) % V;
            MethodCount[i][k] = (MethodCount[i-1][j] + MethodCount[i][k]) % MAX;
        }
    }
    return MethodCount[n][0] - 1;
}

int main()
{
    memset(MethodCount, 0, sizeof(MethodCount));
    scanf("%d %d", &n, &V);
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    cout << CalculateTotalMethods(n, V) % MAX << endl;    

    system("pause");
    return 0;
}