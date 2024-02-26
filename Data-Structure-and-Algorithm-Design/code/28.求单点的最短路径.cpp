#include<bits/stdc++.h>
using namespace std;
#define MAX_VERTEX_NUM 1010
#define INF 0x3f3f3f3f
    
int VertexNum = 0, EdgeNum = 0;
char SourceVertex;
int dist[MAX_VERTEX_NUM];    
int Length[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
bool visited[MAX_VERTEX_NUM];
    
void Dijkstra(int Source)
{
    for (int i = 0; i < EdgeNum; i++)
    {
        dist[i] = Length[Source][i];
        visited[i] = false;
    }

    visited[Source] = true;
    dist[Source] = 0;

    for (int i = 0; i < EdgeNum; i++)
    {
        int loc, temp = INF;
        for (int j = 0; j < EdgeNum; j++)
        {
            if (!visited[j] && temp > dist[j])
            {
                temp = dist[j];
                loc = j;
            }
        }

        if (temp == INF) break;
        visited[loc] = true;

        for (int j = 0; j < EdgeNum; j++)
        {
            if (!visited[j] && dist[loc] + Length[loc][j] < dist[j])
            {
                dist[j] = dist[loc] + Length[loc][j];
            }
        }
    }
}

int main()
{
    scanf("%d,%d,%c\n", &VertexNum, &EdgeNum, &SourceVertex);
    for (int i = 0; i < EdgeNum; i++)
    {
        for (int j = 0; j < VertexNum; j++)
        {
            if (i == j) Length[i][j] = 0;
            else Length[i][j] = INF;
        }
    }
    
    for (int i = 0; i < EdgeNum; i++)
    {
        char StartVertex, EndVertex;
        int length;
        scanf("<%c,%c,%d>\n", &StartVertex, &EndVertex, &length);
        int start = StartVertex - 'a';
        int end = EndVertex - 'a';
        Length[start][end] = min(Length[start][end], length);
    }
    
    int Source = SourceVertex - 'a';
    Dijkstra(Source);

    for (int i = 0; i < VertexNum; i++)
    {
        cout << (char)(i + 'a') << ":" << dist[i] << endl;
    }

    return 0;
}