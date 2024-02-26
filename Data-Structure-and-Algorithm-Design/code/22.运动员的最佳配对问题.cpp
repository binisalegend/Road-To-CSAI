/*
 * @Description: Using backtracking method to solve athlete pairing problems
 * @Author: binisalegend
 * @Date: 2023-10-24 19:51:39
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-25 00:08:30
 */
#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 15

int MaleAthlete[MAXSIZE][MAXSIZE];
int FemaleAthlete[MAXSIZE][MAXSIZE];
int MatchingAdvantages[MAXSIZE][MAXSIZE];
int MaxMaleMatchingAdvantages[MAXSIZE];
bool FemaleAthleteChosen[MAXSIZE] = {false};

int MaxAdvantages = 0, TempAdvantage = 0, AthleteNum = 0;

void BackTracking(int t)
{
    if (t >= AthleteNum)
    {
        MaxAdvantages = max(MaxAdvantages, TempAdvantage);
        return;
    }
        
    int ctn = 0;

    for (int i = t; i < AthleteNum; i++)
    {
        ctn += MaxMaleMatchingAdvantages[i];
    }

    if (TempAdvantage + ctn < MaxAdvantages)  return;

    for (int i = 0; i < AthleteNum; i++)
    {
        if (!FemaleAthleteChosen[i]) 
        {
            FemaleAthleteChosen[i] = true;
            TempAdvantage += MatchingAdvantages[t][i];
            BackTracking(t + 1);
            FemaleAthleteChosen[i] = false;
            TempAdvantage -= MatchingAdvantages[t][i];
        }
    }
    
}

int main()
{
    cin >> AthleteNum;

    for (int i = 0; i < AthleteNum; i++)
    {
        for (int j = 0; j < AthleteNum; j++)
        {
            cin >> MaleAthlete[i][j];
        }
    }

    for (int i = 0; i < AthleteNum; i++)
    {
        for (int j = 0; j < AthleteNum; j++)
        {
            cin >> FemaleAthlete[i][j];
            MatchingAdvantages[i][j] = MaleAthlete[j][i] * FemaleAthlete[i][j];
            MaxMaleMatchingAdvantages[i] = max(MaxMaleMatchingAdvantages[i], MatchingAdvantages[i][j]);
        }
    }

    BackTracking(0);
    
    cout << MaxAdvantages << endl;
    system("pause");
    return 0;
}