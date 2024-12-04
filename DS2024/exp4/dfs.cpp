// DFSÀ„∑®
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

