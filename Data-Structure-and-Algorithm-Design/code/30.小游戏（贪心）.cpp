#include<bits/stdc++.h>
using namespace std;
#define MaxVertex 1510
#define Vertex int
#define Key int 

int NumOfVertex = 0;
bool visited[MaxVertex];
int dp[MaxVertex][2];

/* 基于邻接表实现的无向图类 */
class GraphAdjList {
public:
    // 邻接表，key: 顶点，value：该顶点的所有邻接顶点
    map<Vertex, vector<Vertex>> adjList;

    /* 构造方法 */
    GraphAdjList(const vector<vector<Vertex>> &edges) {
        // 添加所有顶点
        for (const vector<Vertex> &edge : edges) {
            addVertex(edge[0]);
        }
    }

    /* 获取顶点数量 */
    int size() {
        return adjList.size();
    }

    /* 添加边 */
    void addEdge(Vertex vet1, Vertex vet2) {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
            throw invalid_argument("不存在顶点");
        // 添加边 vet1 - vet2
        adjList[vet1].push_back(vet2);
        adjList[vet2].push_back(vet1);
    }

    /* 添加顶点 */
    void addVertex(Vertex vet) {
        if (!adjList.count(vet)) {
            // 在邻接表中添加一个新链表
            adjList[vet] = vector<int>();
        }
    }
};

void dfs(GraphAdjList &graph, Vertex root)
{
    visited[root] = true;
    // 依次遍历根节点的每个子节点
    for (Vertex child : graph.adjList[root])
    {
        if (visited[child]) continue;
        dfs(graph, child);
        dp[root][0] += dp[child][1];
        dp[root][1] += min(dp[child][0], dp[child][1]);
    }
    dp[root][1] += 1;
}

int main()
{
    while (scanf("%d", &NumOfVertex) != EOF)
    {
        memset(visited, false, sizeof(visited));
        memset(dp, 0, sizeof(dp));
        // 创建图和第一个节点
        vector<vector<Vertex>> edges;
        vector<Vertex> edge;
        int FirstVertex, NumOfEdgeConnected;
        scanf("%d:(%d) ", &FirstVertex, &NumOfEdgeConnected);
        edge.push_back(FirstVertex);
        edges.push_back(edge);
        GraphAdjList graph(edges);

        for (int i = 0; i < NumOfEdgeConnected; i++)
        {
            int vet;
            scanf("%d", &vet);
            graph.addVertex(vet);
            graph.addEdge(FirstVertex, vet);
        }
        NumOfVertex--;

        while (NumOfVertex--)
        {
            int SourceVertex, NumOfEdgeConnected;
            scanf("%d:(%d) ", &SourceVertex, &NumOfEdgeConnected);
            graph.addVertex(SourceVertex);
            for (int i = 0; i < NumOfEdgeConnected; i++)
            {
                int vet;
                scanf("%d", &vet);
                graph.addVertex(vet);
                graph.addEdge(SourceVertex, vet);
            }
        }

        dfs(graph, FirstVertex);
        printf("%d\n", min(dp[FirstVertex][0], dp[FirstVertex][1]));
    }
    return 0;
}