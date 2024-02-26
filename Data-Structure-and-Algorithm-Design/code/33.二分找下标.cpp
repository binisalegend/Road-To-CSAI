#include<bits/stdc++.h>
using namespace std;

int *Number, *result;
int i = 0;
bool flag = false;

void MergeSort(int left, int right)
{
    int mid = (left + right) / 2;
    if (left <= right)
    {
        if (Number[mid] == mid)
        {
            result[i++] = mid;
            MergeSort(left, mid - 1);
            MergeSort(mid + 1, right);
        }
        else if (Number[mid] > mid)
        {
            if (!flag) MergeSort(left, mid - 1);
            else MergeSort(mid + 1, right);
        }
        else if (Number[mid] < mid)
        {
            if (!flag) MergeSort(mid + 1, right);
            else MergeSort(left, mid - 1);
        }
    }
}


int main()
{
    int NumOfNumber;
    scanf("%d",&NumOfNumber);

    Number = (int *)malloc(NumOfNumber * sizeof(int));
    result = (int *)malloc(NumOfNumber * sizeof(int));

    for (int i = 0; i < NumOfNumber; i++)
    {
        scanf("%d", &Number[i]);
    }

    if (Number[0] > Number[NumOfNumber - 1]) flag = true;

    MergeSort(0, NumOfNumber - 1);
    if (i == 0) printf("No ");
    else 
    {
        sort(result, result + i);
        for (int j = 0; j < i; j++)
        {
            printf("%d ", result[j]);
        }
    }
    printf("\n");

    return 0;
}