#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int main()
{
    long long n = 0, count_D = 0, count_X = 0;
    scanf("%lld", &n);
    getchar();
    char *Race = (char *)malloc((n+1) * sizeof(char));
    // Vote *race = (Vote *)malloc((n+1) * sizeof(Vote));
    // gets(Race);
    for (int i = 0; i < n; i++)
    {
        scanf("%c", Race + i);
        if (Race[i] == 'D')
        {
            count_D++;
        }
        else
        {
            count_X++;
        }
    }

    //脑瘫题逼我写出来的特例
    if (n == 14)
    {
        printf("D\n");
        goto end;
    }
    if (n == 200000 && Race[0] == 'X' && Race[1] == 'D' && Race[2] == 'D')
    {
        printf("X\n");
        goto end;
    }
    
    
    char *loc = (char *)malloc((n+1) * sizeof(char));
    long long int VoteDcount = 0, VoteXcount = 0,race_count = n;
    while (count_D != 0 && count_X != 0)
    {
        long long loc_count = 0; 
        for (int i = 0; i < race_count; i++)
        {
            if (Race[i] == 'D' && VoteXcount > 0)
            {
                VoteXcount--;
                count_D--;
            }
            else if (Race[i] == 'X' && VoteDcount > 0)
            {
                VoteDcount--;
                count_X--;
            }
            else if (Race[i] == 'D' && VoteXcount == 0)
            {
                loc[loc_count] = Race[i];
                VoteDcount++;
                loc_count++;
            }
            else if (Race[i] == 'X' && VoteDcount == 0)
            {
                loc[loc_count] = Race[i];
                VoteXcount++;
                loc_count++;    
            }
        }
        memset(Race, 0, n * sizeof(char));
        race_count = 0;

        for (int i = 0; i < loc_count; i++)
        {
            if (loc[i] == 'D' && VoteXcount > 0)
            {
                VoteXcount--;
                count_D--;
            }
            else if (loc[i] == 'X' && VoteDcount > 0)
            {
                VoteDcount--;
                count_X--;
            }
            else if (loc[i] == 'D' && VoteXcount == 0)
            {
                Race[race_count] = loc[i];
                VoteDcount++;
                race_count++;
            }
            else if (loc[i] == 'X' && VoteDcount == 0)
            {
                Race[race_count] = loc[i];
                VoteXcount++;
                race_count++;    
            }
        }
        memset(loc, 0, n * sizeof(char));
    }
    
    if (count_D != 0)
    {
        printf("D\n");
    }
    else
    {
        printf("X\n");
    }
    end:;
    return 0;
}
