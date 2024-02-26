#include<bits/stdc++.h>
#include<stdbool.h>
using namespace std;

typedef struct 
{
    int time = 0;
    int value = 0;
    int score;
}tvs;

tvs question[26];
long long score_rem[26][30005];
int n = 0, m = 0;
long long TotalScore = 0;

int cmp(const void *a, const void *b)
{
    return ((*(tvs*)b)).value- ((*(tvs*)a)).value;
}

long long CalculateMaxScore(int que_num, int total_time)
{
    int jMax = min(question[0].time-1, total_time);
    for (int i = 0; i <= jMax; i++)
    {
        score_rem[1][i] = 0;
    }
    for (int i = question[0].time; i <= total_time; i++)
    {
        score_rem[1][i] = question[0].score;
    }

    for (int i = 1; i < que_num; i++)
    {
        jMax = min(question[i].time-1, total_time);
        for (int j = 0; j <= jMax; j++)
        {
            score_rem[i+1][j] = score_rem[i][j];
        }
        for (int j = question[i].time; j <= total_time; j++)
        {
            score_rem[i+1][j] = max(score_rem[i][j], score_rem[i][j-question[i].time] + question[i].score);
        }
    }
    return score_rem[que_num][total_time];
}

int main()
{
    memset(question, 0, sizeof(question));
    memset(score_rem, 0, sizeof(score_rem));
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &question[i].time, &question[i].value);
        question[i].score = question[i].time * question[i].value;
    }
    qsort(question, m, sizeof(question[1]), cmp);

    TotalScore = CalculateMaxScore(m, n);
    
    printf("%lld\n", TotalScore);

    system("pause");
    return 0;
}