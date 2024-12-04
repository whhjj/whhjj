#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <queue>

using namespace std;

// ͼ�����ݽṹ�����б�Ȩ�أ�
class Graph {
public:
    vector<vector<pair<int, int>>> adjList;  // ÿ���ڽӱ����һ�� pair (�ڽӵ�, Ȩ��)
    int V;  // ��������

    Graph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
    }

    // ��ӱ� (u, v, weight)
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});  // ����ͼ
    }

    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "���� " << i << ": ";
            for (auto v : adjList[i]) {
                cout << "(" << v.first << ", " << v.second << ") ";
            }
            cout << endl;
        }
    }
};

// Dijkstra�㷨����Դ���·����
void Dijkstra(Graph &graph, int start) {
    vector<int> dist(graph.V, INT_MAX);
    dist[start] = 0;
    set<pair<int, int>> pq; // �洢(���룬�ڵ�)
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

    // ������·��
    cout << "�������·�� " << start << ":\n";
    for (int i = 0; i < graph.V; ++i) {
        if (dist[i] == INT_MAX) {
            cout << "�붥��ľ��� " << i << " �������\n";
        } else {
            cout << "�붥��ľ��� " << i << " �� " << dist[i] << "\n";
        }
    }
}

// Prim�㷨����С��������
void Prim(Graph &graph) {
    vector<int> key(graph.V, INT_MAX);  // ��¼ÿ���ڵ����С��Ȩ��
    vector<int> parent(graph.V, -1);    // ��¼���Ľṹ
    vector<bool> inMST(graph.V, false); // ��¼�ڵ��Ƿ�����С��������
    key[0] = 0;  // �ӽڵ�0��ʼ
    set<pair<int, int>> pq;  // �洢(Ȩ�أ��ڵ�)
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

    // �����С�������ı�
    cout << "��С�������ı�:\n";
    for (int i = 1; i < graph.V; ++i) {
        cout << parent[i] << " - " << i << " Ȩ�� " << key[i] << endl;
    }
}

int main() {
    // ����ͼʵ������Ӵ�Ȩ�صı�
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 2);
    g.addEdge(2, 5, 5);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 7);

    // ��ӡͼ
    cout << "ͼ�ڽӱ�:\n";
    g.printGraph();

    // Dijkstra����
    cout << "\n���·���㷨:\n";
    Dijkstra(g, 0);

    // Prim����
    cout << "\n��С�������㷨:\n";
    Prim(g);

    return 0;
}

