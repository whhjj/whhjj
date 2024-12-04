#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <set>

using namespace std;

// ͼ�����ݽṹ
class Graph {
public:
    // �ڽӱ��ʾͼ
    vector<list<int>> adjList;
    int V;  // ͼ�Ķ�������

    // ���캯��
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

