#include<bits/stdc++.h>
using namespace std;
#define MaxNumOfContainer 110

typedef struct container
{
    int weight;
    int index = 0;
}Container;    

int TotalWeightMax = 0, NumOfContainer = 0, MaxLoad = 0;
bool ExitSign = false;
Container *weight = NULL;
int *ContainerNo = NULL;

int TotalWeight(int index, int sum)
{
    for (int i = index; i <= NumOfContainer; i++)
    {
        sum += weight[i].weight;
    }
    return sum;
}

void NoOfContainer(bool flag, int index, int sum)
{
    if (ExitSign) return;
    if (index > NumOfContainer)
    {
        if (sum == TotalWeightMax)
        {
            MaxLoad = sum;
            ExitSign = true;
        }
        else if (sum < TotalWeightMax) ;
        MaxLoad = max(MaxLoad, sum);
        return;
    }

    if (flag == false)
    {
        ContainerNo[index] = 0;
        NoOfContainer(true, index + 1, sum);
        NoOfContainer(false, index + 1, sum);
    }
    else
    {
        ContainerNo[index] = weight[index].index;
        sum += weight[index].weight;
        if (sum == TotalWeightMax)
        {
            MaxLoad = sum;
            ExitSign = true;
            return;
        }
        if (sum > TotalWeightMax) return;

        if (TotalWeight(index+1, sum) <= MaxLoad) return;
        NoOfContainer(true, index + 1, sum);
        NoOfContainer(false, index + 1, sum);
    }
    
}


int main()
{
    scanf("%d %d", &TotalWeightMax, &NumOfContainer);

    weight = new Container[NumOfContainer + 1];
    ContainerNo = new int[NumOfContainer + 1];
    memset(ContainerNo, 0, sizeof(ContainerNo));
    for (int i = 1; i <= NumOfContainer; i++)
    {
        cin >> weight[i].weight;
        weight[i].index = i;
    }

    // 导出编号列表
    NoOfContainer(true, 1, 0);
    NoOfContainer(false, 1, 0);

    // 对编号列表按照编号大小进行排序
    printf("%d\n", MaxLoad);
    for (int i = 0; i <= NumOfContainer; i++)
    {
        if (ContainerNo[i])
        {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}

