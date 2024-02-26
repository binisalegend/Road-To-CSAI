#include<bits/stdc++.h>
using namespace std;
#define MAX 1010

bool visited[MAX]; // 访问标记
int NumOfVertex, NumOfEdge; // 节点数，边数
int graph[MAX][MAX]; // 图
int NodePenetration[MAX]; // 节点的入度
int EarlyStart[MAX]; // 最早开始时间
int LateStart[MAX]; // 最晚开始时间
int PathLength[MAX]; // 路径长度
int MaxPath = 0; // 最长路径
list<int> Penetration_0; // 入度为0的节点
vector<int> Penetration_result; // 入度为1的节点
vector<int> CriticalPath; // 关键路径节点 
vector<vector<int>> result; // 关键路径节点构成的路径集合
vector<int> path; // 路径
map<int, vector<int>> AdjacencyList; // 邻接表
map<int, string> VertexToNum; // 节点名称到节点编号

// 计算最早开始时间
void CalculateEarlyStart() 
{
    memset(EarlyStart, 0, sizeof(EarlyStart));

    for (auto i: Penetration_result) 
    {
        for (int j = 0; j < NumOfVertex; j++) 
        {
            if (graph[i][j] != 0) 
            {
                if (EarlyStart[i] + graph[i][j] > EarlyStart[j]) 
                {
                    EarlyStart[j] = EarlyStart[i] + graph[i][j];
                }
            }
        }
    }
}

// 计算最晚开始时间
void CalculateLateStart() 
{
    reverse(Penetration_result.begin(), Penetration_result.end());
    int lastNode = NumOfVertex - 1;
    for (int i = 0; i < NumOfVertex; i++) 
    {
        LateStart[i] = EarlyStart[lastNode];
    }

    for (auto i: Penetration_result) 
    {
        for (int j = NumOfVertex-1; j >= 0; j--) 
        {
            if (graph[j][i] != 0) 
            {
                if (LateStart[i] - graph[j][i] < LateStart[j]) 
                {
                    LateStart[j] = LateStart[i] - graph[j][i];
                }
            }
        }
    }
}

// 遍历所有的关键路径
void DFS(int CurrentNode, int TargetNode)
{
    path.push_back(CurrentNode);

    if (CurrentNode == TargetNode)
    {
        result.push_back(path);
    }
    else
    {
        for (auto i: AdjacencyList[CurrentNode])
        {
            if (std::find(CriticalPath.begin(), CriticalPath.end(), i) != CriticalPath.end() || i == TargetNode) 
            {
                DFS(i, TargetNode);
            }
        }
    }

    path.pop_back();
}

// 打印关键路径
void PrintCriticalPath() 
{
    CalculateEarlyStart();
    CalculateLateStart();
    reverse(Penetration_result.begin(), Penetration_result.end());

    for (auto i: Penetration_result) 
    {
        if (LateStart[i] - EarlyStart[i] == 0)
        {
            CriticalPath.push_back(i);
        }
    }

    memset(visited, false, sizeof(visited));
    DFS(CriticalPath[0], CriticalPath.back());

    sort(result.begin(), result.end());

    for (int j = 0; j < result.size(); j++)
    {
        vector<int> pat = result[j];
        for (int i = 0; i < pat.size() - 1; i++)
        {
            PathLength[j] += graph[pat[i]][pat[i + 1]];
        }
        if (PathLength[j] > MaxPath) MaxPath = PathLength[j];
    }

    for (int j = 0; j < result.size(); j++)
    {
        vector<int> Path = result[j];
        if (PathLength[j] < MaxPath) continue;
        for (int i = 0; i < Path.size(); i++)
        {
            printf("%s", VertexToNum[Path[i]].c_str());
            if (i != Path.size()-1) printf("-");
        }
        printf("\n");
    }
}

// 打印拓扑排序
void PrintTopology()
{
    int Edge = NumOfEdge;
    for (int i = 0; i < NumOfVertex; i++)
    {
        if (NodePenetration[i] == 0)
        {
            Penetration_0.push_back(i);
        }
    }

    while (!Penetration_0.empty())
    {
        Penetration_0.sort();
        int ope = Penetration_0.front();
        Penetration_0.pop_front();
        if (visited[ope]) continue;
        visited[ope] = true;
        Penetration_result.push_back(ope);

        for (int i = 0; i < NumOfVertex; i++)
        {
            if (graph[ope][i] == 0) continue;
            NodePenetration[i]--;
            Edge--;
            if (NodePenetration[i] == 0) Penetration_0.push_back(i);
        }
    }

    if (Edge != 0) 
    {
        printf("NO TOPOLOGICAL PATH\n");
        return;
    }

    for (int i = 0; i < Penetration_result.size(); i++)
    {
        if (i == Penetration_result.size()-1) printf("%s\n", VertexToNum[Penetration_result[i]].c_str());
        else printf("%s-", VertexToNum[Penetration_result[i]].c_str());
    }

    PrintCriticalPath();

    return;
}

int main()
{
    scanf("%d,%d\n", &NumOfVertex, &NumOfEdge);
    memset(graph, 0, sizeof(graph));
    memset(NodePenetration, 0, sizeof(NodePenetration));
    memset(visited, false, sizeof(visited));
    memset(PathLength, 0, sizeof(PathLength));
    Penetration_0.clear();
    Penetration_result.clear();

    string str;
    cin >> str;
    stringstream ss(str);
    vector<string> VertexList;
    string loc;

    while (getline(ss, loc, ','))
    {
        VertexList.push_back(loc);
    }

    for (int i = 0; i < NumOfVertex; i++)
    {
        VertexToNum[i] = VertexList[i];
    }

    for (int i = 0; i < NumOfEdge; i++)
    {
        int vet1, vet2, length;
        char ch;
        cin >> ch >> vet1 >> ch >> vet2 >> ch >> length >> ch >> ch; 
        NodePenetration[vet2]++;
        graph[vet1][vet2] = length;
        AdjacencyList[vet1].push_back(vet2);
    }
    PrintTopology();

    return 0;
}