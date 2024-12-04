#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// 图的数据结构
class Graph {
public:
    vector<list<int>> adjList;
    int V;  // 顶点数量

    Graph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
    }

    // 添加边
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // 无向图
    }

    // 打印图
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "顶点 " << i << ": ";
            for (int v : adjList[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

// BFS算法
void BFS(Graph &graph, int start) {
    vector<bool> visited(graph.V, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        cout << vertex << " ";

        for (int neighbor : graph.adjList[vertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

// DFS算法
void DFS(Graph &graph, int start) {
    vector<bool> visited(graph.V, false);
    stack<int> s;
    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int vertex = s.top();
        s.pop();
        cout << vertex << " ";

        for (int neighbor : graph.adjList[vertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    // 创建图实例并添加边
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 5);

    // 打印图
    cout << "图邻接表:" << endl;
    g.printGraph();

    // BFS测试
    cout << "BFS 从顶点0开始:" << endl;
    BFS(g, 0);

    // DFS测试
    cout << "DFS 从顶点0开始:" << endl;
    DFS(g, 0);

    return 0;
}

