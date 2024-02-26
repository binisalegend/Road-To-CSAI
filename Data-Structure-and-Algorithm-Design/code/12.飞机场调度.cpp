#include<bits/stdc++.h>
using namespace std;
    
int RunwaysNum, LandingTime, LaunchingTime;  //跑道数量，降落所需时间，起飞所需时间
int CurrentTime = 0;  //当前时间
int LandingNum, LaunchingNum;  //每轮次需要降落和起飞的飞机数量
int WaitingLand, WaitingLaunch;   //等待降落和起飞的飞机数量
int LandingNode = 5001, LaunchingNode = 1; //降落和起飞飞机编号
int TotalLandingPlane = 0, TotalLaunchingPlane = 0;  //起飞和降落飞机总数
int *LandingWaitingTimeRecord, *LaunchingWaitingTimeRecord;  //记录飞机等候时间
float TotalLandingWaitingTime = 0, TotalLaunchingWaitingTime = 0; //记录飞机总等候时长

typedef struct 
{
    int LandingNo;
    int WaitingTime = 0;
}LandInformation;  //起飞飞机编号和等待时间

typedef struct 
{
    int LaunchingNo;
    int WaitingTime = 0;
}LaunchInformation;  //降落飞机编号和等待时间

typedef struct
{
    bool RunwayCondition = true;
    int BusyTime;
    int EndBusyTime;
}RunwayInformation;  //跑道空闲状况和忙碌时间


queue<LandInformation> Landing;   //降落排队队列
queue<LaunchInformation> Launching;  //起飞排队队列
RunwayInformation *Runway; //跑道状况数组
    
void RunwayBusyJudging() //更改跑道状态函数
{
    for (int i = 1; i <= RunwaysNum; i++)
    {
        if (CurrentTime == Runway[i].EndBusyTime)
        {
            printf("runway %02d is free\n", i);
            Runway[i].RunwayCondition = true;
        }
    }
    return;
}

void Takeoff_Land()   //执行起飞降落操作函数
{
    for (int i = 1; i <= RunwaysNum; i++)
    {
        if (Runway[i].RunwayCondition == true)
        {
            if (!Landing.empty())
            {
                printf("airplane %04d is ready to land on runway %02d\n", Landing.front().LandingNo, i);
                Runway[i].RunwayCondition = false;
                LandingWaitingTimeRecord[Landing.front().LandingNo-5000] = CurrentTime - Landing.front().WaitingTime;
                Runway[i].EndBusyTime = CurrentTime + LandingTime;
                Runway[i].BusyTime += LandingTime;
                WaitingLand--;
                Landing.pop();
            }
            else if (!Launching.empty())  //注意要加上判定起飞队列是否为空，不然可能没有front()，会无效内存
            {
                printf("airplane %04d is ready to takeoff on runway %02d\n", Launching.front().LaunchingNo, i);
                Runway[i].RunwayCondition = false;
                LaunchingWaitingTimeRecord[Launching.front().LaunchingNo] = CurrentTime - Launching.front().WaitingTime;
                Runway[i].EndBusyTime = CurrentTime + LaunchingTime;
                Runway[i].BusyTime += LaunchingTime;
                WaitingLaunch--;
                Launching.pop();
            }
        }
    }
    return;
}

void WaitingForLaunch(int Launching_num)   //在队列中加入待起飞飞机编号信息
{
    for (int i = 0; i < Launching_num; i++)
    {
        LaunchInformation Launch_plane;
        Launch_plane.LaunchingNo = LaunchingNode;
        LaunchingNode++;
        Launch_plane.WaitingTime = CurrentTime;
        Launching.push(Launch_plane);
        WaitingLaunch++;
    }
    return;
}

void WaitingForLand(int Landing_num) //在队列中加入待降落飞机编号信息
{
    for (int i = 0; i < Landing_num; i++)
    {
        LandInformation Land_plane;
        Land_plane.LandingNo= LandingNode;
        LandingNode++;
        Land_plane.WaitingTime = CurrentTime;
        Landing.push(Land_plane);
        WaitingLand++;
    }
    return;
}

int main()
{
    scanf("%d %d %d", &RunwaysNum, &LandingTime, &LaunchingTime);

    //初始化跑道状态
    Runway = (RunwayInformation *)malloc((RunwaysNum + 3) * sizeof(RunwayInformation));
    for (int i = 0; i <= RunwaysNum; i++)
    {
        Runway[i].BusyTime = 0;
        Runway[i].RunwayCondition = true;
    }
    
    //有点小抽象，不能用RunwaysNum嗷，一开始犯病后两个用例会无效内存
    LandingWaitingTimeRecord = (int *)malloc(((20000 + 1)* sizeof(int)));   
    LaunchingWaitingTimeRecord = (int *)malloc(((20000 + 1)* sizeof(int)));

    printf("Current Time: %4d\n", CurrentTime);
    CurrentTime++;

    //开始接收第一组数据
    scanf("%d %d", &LandingNum, &LaunchingNum);
    TotalLandingPlane += LandingNum;
    TotalLaunchingPlane += LaunchingNum;
    while ((LandingNum >= 0) || (LaunchingNum >= 0))
    {
        WaitingForLand(LandingNum);
        WaitingForLaunch(LaunchingNum);
        Takeoff_Land();

        printf("Current Time: %4d\n", CurrentTime);
        CurrentTime++;
        RunwayBusyJudging();
        scanf("%d %d", &LandingNum, &LaunchingNum);
        if (LandingNum >= 0)
        {
            TotalLandingPlane += LandingNum;
        }
        if (LaunchingNum >= 0)
        {
            TotalLaunchingPlane += LaunchingNum;
        }
    }

    //数据接收完成，运行到完成所有起降
    while ((WaitingLand != 0) || (WaitingLaunch != 0))
    {
        Takeoff_Land();
        printf("Current Time: %4d\n", CurrentTime);
        CurrentTime++;
        RunwayBusyJudging();
    }
    
    for (int i = 1; i <= RunwaysNum; i++)
    {
        Runway[i].EndBusyTime--;
    }
    
    bool flag = true;   //提前先验证一下是否在前一过程中已经完成启停
    for (int i = 1; i <= RunwaysNum; i++)
    {
        if (!Runway[i].RunwayCondition)
        {
            flag = false;
        }
    }

    while(!flag)
    {
        flag = true;
        printf("Current Time: %4d\n", CurrentTime);
        RunwayBusyJudging();
        CurrentTime++;
        for (int i = 1; i <= RunwaysNum; i++)
        {
            if (!Runway[i].RunwayCondition)
            {
                flag = false;
                break;
            }
        }
    }

    //计算总等候时长
    for (int i = 1; i <= TotalLandingPlane; i++)
    {
        TotalLandingWaitingTime += LandingWaitingTimeRecord[i];
    }
    for (int i = 1; i <= TotalLaunchingPlane; i++)
    {
        TotalLaunchingWaitingTime += LaunchingWaitingTimeRecord[i];
    }

    printf("simulation finished\n");
    printf("simulation time: %4d\n", CurrentTime-1);
    if (TotalLandingPlane != 0)
    printf("average waiting time of landing: %4.1f\n", TotalLandingWaitingTime / TotalLandingPlane * 1.0);
    else printf("average waiting time of landing: %4.1f\n", 0);  //加个特例，防止出现一共就没有飞机的情况
    if (TotalLaunchingPlane != 0)
    printf("average waiting time of takeoff: %4.1f\n", TotalLaunchingWaitingTime / TotalLaunchingPlane * 1.0);
    else printf("average waiting time of takeoff: %4.1f\n", 0); 

    float AvarageBusyTime = 0;

    for (int i = 1; i <= RunwaysNum; i++)
    {
        AvarageBusyTime += Runway[i].BusyTime;
        printf("runway %02d busy time: %4d\n", i, Runway[i].BusyTime);
    }
    AvarageBusyTime = AvarageBusyTime / RunwaysNum;
    float percentage = AvarageBusyTime * 100 / (CurrentTime - 1);
    printf("runway average busy time percentage: %4.1f", percentage);
    printf("%\n");
    system("pause");
    return 0;
}