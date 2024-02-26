#include<bits/stdc++.h>
#include<stdbool.h>
using namespace std;

int Max_x, Max_y, C_x, C_y;
bool Stolen[21][21] = {false};
long long int path_count[21][21] = {0};


void PathCount()
{
    for (int x = 0; x <= Max_x; x++)
    {
        for (int y = 0; y <= Max_y; y++)
        {
            if(Stolen[x][y] == true)
            {
                path_count[x][y] = 0;
            }
            else if (x == 0 && y == 0)
            {
                path_count[0][0] = 1;
            }
            else
            {
                if (x-1 >= 0 && y-1 < 0)
                {
                    path_count[x][y] = path_count[x-1][y];
                }
                else if (x-1 < 0 && y-1 >= 0)
                {
                    path_count[x][y] = path_count[x][y-1];
                }
                else
                {
                    path_count[x][y] = path_count[x-1][y] + path_count[x][y-1];
                }
            }
        }
    }
}

void StolenCheck(int x, int y)
{
    Stolen[x][y] = true;
    if (x - 2 >= 0 && y - 1 >= 0)
    {
        Stolen[x-2][y-1] = true;
    }
    if (x - 1 >= 0 && y - 2 >= 0)
    {
        Stolen[x-1][y-2] = true;
    }
    if (x + 1 <= Max_x && y - 2 >= 0)
    {
        Stolen[x+1][y-2] = true;
    }
    if (x + 2 <= Max_x && y - 1 >= 0)
    {
        Stolen[x+2][y-1] = true;
    }
    if (x - 2 >= 0 && y + 1 <= Max_y)
    {
        Stolen[x-2][y+1] = true;
    }
    if (x - 1 >= 0 && y + 2 <= Max_y)
    {
        Stolen[x-1][y+2] = true;
    }
    if (x + 1 <= Max_x && y + 1 <= Max_y)
    {
        Stolen[x+1][y+2] = true;
    }
    if (x + 2 <= Max_x && y + 1 <= Max_y)
    {
        Stolen[x+2][y+1] = true;
    }
}

int main()
{
    scanf("%d %d %d %d", &Max_x, &Max_y, &C_x, &C_y);
    StolenCheck(C_x, C_y);
    PathCount();
    cout << path_count[Max_x][Max_y] << endl;

    system("pause");
    return 0;
}


// int PathCount(int x, int y)
// {
//     if (x == 0 && y == 0)
//     {
//         return 0;
//     }
//     else if (x == 0)
//     {
//         for (int i = 0; i < y; i++)
//         {
//             if (Stolen[0][i] == true)
//             {
//                 return 0;
//             }
//         }
//         return 1;
//     }
//     else if (y == 0)
//     {
//         for (int i = 0; i < x; i++)
//         {
//             if (Stolen[i][0] == true)
//             {
//                 return 0;
//             }
//         }
//         return 1;
//     }
//     else
//     {
//         if (Stolen[x-1][y] == true && Stolen[x][y-1] == false)
//         {
//             return PathCount(x, y-1);
//         }
//         else if (Stolen[x-1][y] == false && Stolen[x][y-1] == true)
//         {
//             return PathCount(x-1, y);
//         }
//         else if (Stolen[x-1][y] == true && Stolen[x][y-1] == true)
//         {
//             return 0;
//         }
//         else
//         {
//             return PathCount(x, y-1) + PathCount(x-1, y);
//         }
//     }
// }