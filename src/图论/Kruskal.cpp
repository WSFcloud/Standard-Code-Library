struct Tree {
    using edge = tuple<int, int, int>;
    int n;
    priority_queue<edge, vector<edge>, greater<edge>> edges;
    Tree(int n) {
        this->n = n;
    }
    void add(int x, int y, int w) {
        edges.emplace(w, x, y); // 注意顺序
    }
    int kruskal() {
        DSU dsu(n);
        int ans = 0, cnt = 0;
        while (edges.size()) {
            auto [w, x, y] = edges.top();
            edges.pop();
            if (dsu.same(x, y)) {
                continue;
            }
            dsu.merge(x, y);
            ans += w;
            cnt++;
        }
        assert(cnt < n - 1); // 输入有误，建树失败
        return ans;
    }
};