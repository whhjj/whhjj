#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// ͼ�����ݽṹ
class Graph {
public:
    vector<list<int>> adjList;
    int V;  // ��������

    Graph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
    }

    // ��ӱ�
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // ����ͼ
    }

    // ��ӡͼ
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "���� " << i << ": ";
            for (int v : adjList[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

// BFS�㷨
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

// DFS�㷨
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
    // ����ͼʵ������ӱ�
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 5);

    // ��ӡͼ
    cout << "ͼ�ڽӱ�:" << endl;
    g.printGraph();

    // BFS����
    cout << "BFS �Ӷ���0��ʼ:" << endl;
    BFS(g, 0);

    // DFS����
    cout << "DFS �Ӷ���0��ʼ:" << endl;
    DFS(g, 0);

    return 0;
}

