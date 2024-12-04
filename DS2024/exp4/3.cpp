#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <queue>

using namespace std;

// 图的数据结构（带有边权重）
class Graph {
public:
    vector<vector<pair<int, int>>> adjList;  // 每个邻接表包含一个 pair (邻接点, 权重)
    int V;  // 顶点数量

    Graph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
    }

    // 添加边 (u, v, weight)
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});  // 无向图
    }

    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "顶点 " << i << ": ";
            for (auto v : adjList[i]) {
                cout << "(" << v.first << ", " << v.second << ") ";
            }
            cout << endl;
        }
    }
};

// Dijkstra算法（单源最短路径）
void Dijkstra(Graph &graph, int start) {
    vector<int> dist(graph.V, INT_MAX);
    dist[start] = 0;
    set<pair<int, int>> pq; // 存储(距离，节点)
    pq.insert({0, start});

    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());

        for (auto neighbor : graph.adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                pq.erase({dist[v], v});
                dist[v] = dist[u] + weight;
                pq.insert({dist[v], v});
            }
        }
    }

    // 输出最短路径
    cout << "顶点最短路径 " << start << ":\n";
    for (int i = 0; i < graph.V; ++i) {
        if (dist[i] == INT_MAX) {
            cout << "与顶点的距离 " << i << " 是无穷大\n";
        } else {
            cout << "与顶点的距离 " << i << " 是 " << dist[i] << "\n";
        }
    }
}

// Prim算法（最小生成树）
void Prim(Graph &graph) {
    vector<int> key(graph.V, INT_MAX);  // 记录每个节点的最小边权重
    vector<int> parent(graph.V, -1);    // 记录树的结构
    vector<bool> inMST(graph.V, false); // 记录节点是否在最小生成树中
    key[0] = 0;  // 从节点0开始
    set<pair<int, int>> pq;  // 存储(权重，节点)
    pq.insert({0, 0});

    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());
        inMST[u] = true;

        for (auto neighbor : graph.adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && weight < key[v]) {
                pq.erase({key[v], v});
                key[v] = weight;
                pq.insert({key[v], v});
                parent[v] = u;
            }
        }
    }

    // 输出最小生成树的边
    cout << "最小生成树的边:\n";
    for (int i = 1; i < graph.V; ++i) {
        cout << parent[i] << " - " << i << " 权重 " << key[i] << endl;
    }
}

int main() {
    // 创建图实例并添加带权重的边
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 2);
    g.addEdge(2, 5, 5);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 7);

    // 打印图
    cout << "图邻接表:\n";
    g.printGraph();

    // Dijkstra测试
    cout << "\n最短路径算法:\n";
    Dijkstra(g, 0);

    // Prim测试
    cout << "\n最小生成树算法:\n";
    Prim(g);

    return 0;
}

