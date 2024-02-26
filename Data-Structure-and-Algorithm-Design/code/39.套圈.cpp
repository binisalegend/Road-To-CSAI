#include<bits/stdc++.h>
using namespace std;

vector<pair<double, double>> location;

double getDistance(pair<double, double> a, pair<double, double> b)
{
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

// 套环游戏，找到最大的环半径，一次只能套到一个点

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        location.push_back({x, y});
    }

    double minRadius = 1e9;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;
            minRadius = min(minRadius, getDistance(location[i], location[j]) / 2);
        }
    }
    printf("%.2lf\n", minRadius);

    return 0;
}