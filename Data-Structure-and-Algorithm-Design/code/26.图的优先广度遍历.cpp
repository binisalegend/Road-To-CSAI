#include<bits/stdc++.h>
using namespace std;

vector<char> Vertex;
queue<char> BFSQueue;
int edges[100][100] = {0};
bool visited[100] = {false};

void PrintMap()
{
	int length = Vertex.size();
	cout << "the ALGraph is" << endl;
	for (int i = 0; i < length; i++)
	{
		cout << Vertex[i];
		for (int j = length - 1; j >= 0; j--)
		{
			if (edges[i][j] == 1) cout << " " << j;
		}
		cout << endl;
	}
	return;	
}

void PrintBFS()
{
	cout << "the Breadth-First-Seacrh list:";
	for (int i = 0; i < Vertex.size(); i++)
	{
		if (visited[i] == false)
		{
			BFSQueue.push(Vertex[i]);
			visited[i] = true;
		}

		while (!BFSQueue.empty())
		{
			char loc = BFSQueue.front();
			BFSQueue.pop();
			cout << loc;

			int tmp = loc - 'a';
			for (int j = Vertex.size() - 1; j >= 0; j--)
			{
				if (edges[tmp][j] == 1 && visited[j] == false)
				{
					BFSQueue.push(Vertex[j]);
					visited[j] = true;
				}
			}
		}
	}
	cout << endl;
	return;
}

int main()
{
	char loc;
	cin >> loc;
	while (loc != '*')	
	{
		Vertex.push_back(loc);
		cin >> loc;
	}

	int vet1, vet2;
	scanf("%d,%d\n", &vet1, &vet2);
	while (vet1 != -1 && vet2 != -1)
	{
		edges[vet1][vet2] = 1;
		edges[vet2][vet1] = 1;
		scanf("%d,%d\n", &vet1, &vet2);
	}

	PrintMap();
	PrintBFS();
	return 0;
}

// 用面向对象写的，傻逼乐学只能接收一种输出顺序，就必须要按照结构数组来写，重写吧 
// #include <bits/stdc++.h>
// using namespace std;

// #define Vertex int
// #define Key char

// /* 基于邻接表实现的无向图类 */
// class GraphAdjList {
// public:
//     // 邻接表，key: 顶点，value：该顶点的所有邻接顶点
//     map<Vertex, vector<Vertex>> adjList;

// 	/* 在 vector 中删除指定节点 */
//     void remove(vector<Vertex> &vec, Vertex vet) {
//         for (int i = 0; i < vec.size(); i++) {
//             if (vec[i] == vet) {
//                 vec.erase(vec.begin() + i);
//                 break;
//             }
//         }
//     }

//     /* 构造方法 */
//     GraphAdjList(const vector<vector<Vertex>> &edges) {
//         // 添加所有顶点
//         for (const vector<Vertex> &edge : edges) {
//             addVertex(edge[0]);
//         }
//     }

// 	/* 删除边 */
//     void removeEdge(Vertex vet1, Vertex vet2) {
//         if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
//             throw invalid_argument("不存在顶点");
//         // 删除边 vet1 - vet2
//         remove(adjList[vet1], vet2);
//         remove(adjList[vet2], vet1);
//     }

//     /* 获取顶点数量 */
//     int size() {
//         return adjList.size();
//     }

//     /* 添加边 */
//     void addEdge(Vertex vet1, Vertex vet2) {
//         if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
//             throw invalid_argument("不存在顶点");
//         // 添加边 vet1 - vet2
//         adjList[vet1].insert(adjList[vet1].begin(), vet2);
//         adjList[vet2].insert(adjList[vet2].begin(), vet1);
//     }

//     /* 添加顶点 */
//     void addVertex(Vertex vet) {
//         if (!adjList.count(vet)) {
//             // 在邻接表中添加一个新链表
//             adjList[vet] = vector<Vertex>();
//         }
//     }

// 	/* 删除顶点 */
//     void removeVertex(Vertex vet) {
//         if (!adjList.count(vet))
//             throw invalid_argument("不存在顶点");
//         // 在邻接表中删除顶点 vet 对应的链表
//         adjList.erase(vet);
//         // 遍历其他顶点的链表，删除所有包含 vet 的边
//         for (auto &adj : adjList) {
//             remove(adj.second, vet);
//         }
//     }

//     /* 打印邻接表 */
//     void print(const map<Vertex, Key> &reverseVertexMap) {
//         cout << "the ALGraph is" << endl;
//         for (auto &adj : adjList) {
//             const auto &key = adj.first;
//             const auto &vec = adj.second;
//             cout << reverseVertexMap.at(key) << " ";
//             for (size_t i = 0; i < vec.size(); i++) {
//                 cout << vec[i];
//                 if (i < vec.size() - 1) {
//                     cout << " ";
//                 }
//             }
//             cout << endl;
//         }
//     }

// 	/*广度优先遍历输出*/
// 	void graphBFS(int startVertex, const map<Vertex, Key> &reverseVertexMap)
// 	{
// 		printf("the Breadth-First-Seacrh list:");
// 		unordered_map<Vertex, bool> visited;
//         queue<Vertex> bfsQueue;

//         bfsQueue.push(startVertex);
//         visited[startVertex] = true;

//         while (!bfsQueue.empty()) {
//             int vertex = bfsQueue.front();
//             cout << reverseVertexMap.at(vertex);
//             bfsQueue.pop();

//             for (const int &neighbor : adjList[vertex]) {
//                 if (!visited[neighbor]) {
//                     bfsQueue.push(neighbor);
//                     visited[neighbor] = true;
//                 }
//             }
//         }
//         cout << endl;
// 	}
// };

// map<Key, Vertex> vertexMap;

// int main() {
//     Key vertex = ' ';
//     Vertex index = 0;

//     vector<vector<Vertex>> edges;
//     cin >> vertex;
//     while (vertex != '*') {
//         vector<Vertex> edge;
//         edge.push_back(index);
//         vertexMap[vertex] = index++;
//         edges.push_back(edge);
//         cin >> vertex;
//     }

//     GraphAdjList graph(edges);

//     Vertex vet1 = -1, vet2 = -1;
//     scanf("%d,%d\n", &vet1, &vet2);

//     while (vet1 != -1 && vet2 != -1) {
//         graph.addEdge(vet1, vet2);
//         scanf("%d,%d\n", &vet1, &vet2);
//     }

//     // 反向映射，从整数到字符
//     map<Vertex, Key> reverseVertexMap;
//     for (const auto &entry : vertexMap) {
//         reverseVertexMap[entry.second] = entry.first;
//     }

//     graph.print(reverseVertexMap);
// 	graph.graphBFS(0, reverseVertexMap);

//     return 0;
// }

