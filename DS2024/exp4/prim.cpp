// Prim算法实现最小生成树
void Prim(Graph &graph) {
    vector<int> key(graph.V, INT_MAX);  // 用于存储节点的最小权重
    vector<int> parent(graph.V, -1);    // 记录树的结构
    vector<bool> inMST(graph.V, false); // 记录顶点是否在最小生成树中
    key[0] = 0;  // 从节点0开始
    set<pair<int, int>> pq;  // 存储(权重，节点)
    pq.insert({0, 0});

    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());
        inMST[u] = true;

        for (int v : graph.adjList[u]) {
            int weight = 1;  // 假设每条边的权重为1
            if (!inMST[v] && weight < key[v]) {
                pq.erase({key[v], v});
                key[v] = weight;
                pq.insert({key[v], v});
                parent[v] = u;
            }
        }
    }

    // 输出最小生成树
    cout << "边 \tWeight" << endl;
    for (int i = 1; i < graph.V; ++i) {
        cout << parent[i] << " - " << i << " \t1" << endl;  // 权重为1
    }
}

