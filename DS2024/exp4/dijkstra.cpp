// Dijkstra�㷨ʵ�����·��
void Dijkstra(Graph &graph, int start) {
    vector<int> dist(graph.V, INT_MAX);
    dist[start] = 0;
    set<pair<int, int>> pq; // �洢(���룬�ڵ�)
    pq.insert({0, start});

    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());

        for (int v : graph.adjList[u]) {
            int weight = 1; // ����ÿ���ߵ�Ȩ��Ϊ1
            if (dist[u] + weight < dist[v]) {
                pq.erase({dist[v], v});
                dist[v] = dist[u] + weight;
                pq.insert({dist[v], v});
            }
        }
    }

    // ������·��
    for (int i = 0; i < graph.V; ++i) {
        cout << "���� " << start << " �� " << i << " �� " << dist[i] << endl;
    }
}

