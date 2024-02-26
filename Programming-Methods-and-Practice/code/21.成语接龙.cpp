#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cstdbool>
#include<bits/stdc++.h>
using namespace std;

#define MAX 1000010
int step[MAX] = {-1};
bool already[MAX] = {false};

int main()
{
    map<int, vector<int>> graph;
    queue<int> idiom;
    int m = 0, flag = 0;
    scanf("%d", &m);
    while (m--)
    {
        int head, tail;
        scanf("%d %*d %*d %d", &head, &tail);
        graph[head].push_back(tail);
    }
    int start[4], end[4];
    scanf("%d %d %d %d", start, start+1, start+2, start+3);
    scanf("%d %d %d %d", end, end+1, end+2, end+3); 

    if(start[0] == end[0] && start[1] == end[1] && start[2] == end[2] && start[3] == end[3])
    {
        printf("1\n");
    }
    else
    {
        idiom.push(start[3]);
        already[start[3]] = true;
        step[start[3]] = 1;
        while (!idiom.empty())
        {
            int loc = idiom.front();
            idiom.pop();
            for (auto i: graph[loc])
            {
                if(already[i] == false)
                {
                    idiom.push(i);
                    already[i] = true;
                    step[i] = step[loc] + 1;
                    if(loc != end[0] && i == end[3])
                    {
                        already[i] = false;
                        step[i]--;
                    }
                    if(loc == end[0] && i == end[3])
                    {
                        printf("%d\n", step[end[3]]);
                        flag = 1;
                        break;
                    }
                }
            }
            if(flag == 1)
            {
                break;
            }
        }
        if(flag == 0)
        {
            printf("-1\n");
        }
    }
    system("pause");
    return 0;
}

