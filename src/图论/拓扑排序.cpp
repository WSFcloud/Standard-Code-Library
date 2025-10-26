vector<int> kahn(vector<vector<int>> &graph) {
    vector<int> res;
    res.reserve(n);
    queue<int> q;
    for (auto i = 1; i <= n; i++) {
        if (ind[i] == 0) { // 入度为0的顶点
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        res.push_back(u);
        for (auto &v : graph[u]) {
            ind[v]--;
            if (ind[v] == 0) {
                q.push(v);
            }
        }
    }
    return res;
}