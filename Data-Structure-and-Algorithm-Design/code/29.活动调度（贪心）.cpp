#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MaxSize = 1e6 + 10;

int NumOfActivities = 0;
int MaxClassRoom = 0;
int ClassroomNeeded = 0;
ll start_timelist[MaxSize], end_timelist[MaxSize];

int main()
{
    scanf("%d\n", &NumOfActivities);
    
    for (int i = 1; i <= NumOfActivities; i++)
    {
        scanf("%lld %lld\n", start_timelist + i, end_timelist + i);
    }

    sort(start_timelist + 1, start_timelist + NumOfActivities + 1);
    sort(end_timelist + 1, end_timelist + NumOfActivities + 1);

    for (int i = 1, j = 1; i <= NumOfActivities; )
    {
        if (start_timelist[i] < end_timelist[j])
        {
            ClassroomNeeded++;
            i++;
        }
        else
        {
            ClassroomNeeded--;
            j++;
        }
        if (ClassroomNeeded >= MaxClassRoom) MaxClassRoom = ClassroomNeeded;
    }

    printf("%d\n", MaxClassRoom);
    return 0;
}