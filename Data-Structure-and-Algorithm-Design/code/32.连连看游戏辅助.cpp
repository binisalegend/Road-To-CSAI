#include<bits/stdc++.h>
using namespace std;
#define MAX 1010

int row, column;
int Start_row, Start_column, End_row, End_column;
int **Map;
int reach[MAX][MAX];

void JudgeIfEliminated(int start_row, int start_column, int count, int dir)
{
    if (count > 3 || start_column < 0 || start_row < 0 || start_column > (column - 1) || start_row > (row - 1)) return;
    if (Map[start_row][start_column] != Map[Start_row][Start_column] && Map[start_row][start_column] != 0) return;
    if (reach[start_row][start_column] == 0 || reach[start_row][start_column] >= count)
    {
        reach[start_row][start_column] = count;
        switch (dir)
        {
            case 1:
            {
                JudgeIfEliminated(start_row - 1, start_column, count, 1);
                JudgeIfEliminated(start_row, start_column + 1, count + 1, 2);
                JudgeIfEliminated(start_row + 1, start_column, count + 1, 3);
                JudgeIfEliminated(start_row, start_column - 1, count + 1, 4);
                break;
            }
            case 2:
            {
                JudgeIfEliminated(start_row - 1, start_column, count + 1, 1);
                JudgeIfEliminated(start_row, start_column + 1, count, 2);
                JudgeIfEliminated(start_row + 1, start_column, count + 1, 3);
                JudgeIfEliminated(start_row, start_column - 1, count + 1, 4);
                break;
            }
            case 3:
            {
                JudgeIfEliminated(start_row - 1, start_column, count + 1, 1);
                JudgeIfEliminated(start_row, start_column + 1, count + 1, 2);
                JudgeIfEliminated(start_row + 1, start_column, count, 3);
                JudgeIfEliminated(start_row, start_column - 1, count + 1, 4);
                break;
            }
            case 4: 
            {
                JudgeIfEliminated(start_row - 1, start_column, count + 1, 1);
                JudgeIfEliminated(start_row, start_column + 1, count + 1, 2);
                JudgeIfEliminated(start_row + 1, start_column, count + 1, 3);
                JudgeIfEliminated(start_row, start_column - 1, count, 4);
                break;
            }
        }
    }
}

int main()
{
    cin >> row >> column;
    memset(reach, 0, sizeof(reach));
    Map = (int **)malloc(sizeof(int *) * (row + 1));
    for (int i = 0; i < row; i++)
    {
        Map[i] = (int *)malloc(sizeof(int) * (column + 1));
        for (int j = 0; j < column; j++)
        {
            cin >> Map[i][j];
        }
    }

    cin >> Start_row >> Start_column >> End_row >> End_column;

    JudgeIfEliminated(Start_row, Start_column, 1, 1);
    JudgeIfEliminated(Start_row, Start_column, 1, 2);
    JudgeIfEliminated(Start_row, Start_column, 1, 3);
    JudgeIfEliminated(Start_row, Start_column, 1, 4);

    if (reach[End_row][End_column] > 0) cout << "TRUE" << endl;
    else cout << "FALSE" << endl;

    return 0;
}