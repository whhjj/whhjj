// Prim�㷨ʵ����С������
void Prim(Graph &graph) {
    vector<int> key(graph.V, INT_MAX);  // ���ڴ洢�ڵ����СȨ��
    vector<int> parent(graph.V, -1);    // ��¼���Ľṹ
    vector<bool> inMST(graph.V, false); // ��¼�����Ƿ�����С��������
    key[0] = 0;  // �ӽڵ�0��ʼ
    set<pair<int, int>> pq;  // �洢(Ȩ�أ��ڵ�)
    pq.insert({0, 0});

    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());
        inMST[u] = true;

        for (int v : graph.adjList[u]) {
            int weight = 1;  // ����ÿ���ߵ�Ȩ��Ϊ1
            if (!inMST[v] && weight < key[v]) {
                pq.erase({key[v], v});
                key[v] = weight;
                pq.insert({key[v], v});
                parent[v] = u;
            }
        }
    }

    // �����С������
    cout << "�� \tWeight" << endl;
    for (int i = 1; i < graph.V; ++i) {
        cout << parent[i] << " - " << i << " \t1" << endl;  // Ȩ��Ϊ1
    }
}

