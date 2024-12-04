// Dijkstra算法实现最短路径
void Dijkstra(Graph &graph, int start) {
    vector<int> dist(graph.V, INT_MAX);
    dist[start] = 0;
    set<pair<int, int>> pq; // 存储(距离，节点)
    pq.insert({0, start});

    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());

        for (int v : graph.adjList[u]) {
            int weight = 1; // 假设每条边的权重为1
            if (dist[u] + weight < dist[v]) {
                pq.erase({dist[v], v});
                dist[v] = dist[u] + weight;
                pq.insert({dist[v], v});
            }
        }
    }

    // 输出最短路径
    for (int i = 0; i < graph.V; ++i) {
        cout << "距离 " << start << " 到 " << i << " 是 " << dist[i] << endl;
    }
}

