#include<bits/stdc++.h>
using namespace std;
#define MAX 100010

long long N = 0, K = 0;
long long *length;

long long CalculateMaxLength(long long a, long long b)
{
    long long min = a, max = b;
    // cout << min << ' ' << max << endl;
    long long mid = (min + max) / 2, count = 0;
    for (int i = 0; i < N; i++)
    {
        count += length[i] / mid;
    }
    if(count >= K)
    {
        return CalculateMaxLength(mid+1, max);
    }
    else
    {
        if(min == max)
        {
            return max - 1;
        }
        else
        {
            return CalculateMaxLength(min, mid);
        }
    }
}

int main()
{
    long long sum = 0;
    cin >> N;
    length = (long long *)malloc((N+1) * sizeof(long long));
    for(long long i = 0; i < N; i++)
    {
        cin >> length[i];
        sum += length[i];
    }
    cin >> K;

    sort(length, length + N);
    if(sum < K)
    {
        cout << 0 << endl;
    }
    else if(N == 1)
    {
        cout << length[0] / K << endl;
    }
    else
    {
        long long Max_len = 0;
        Max_len = CalculateMaxLength(1, length[N-1]);
        cout << Max_len << endl;
    }
    free(length);
    system("pause");
    return 0;
}