#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <set>

using namespace std;

// 图的数据结构
class Graph {
public:
    // 邻接表表示图
    vector<list<int>> adjList;
    int V;  // 图的顶点数量

    // 构造函数
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

