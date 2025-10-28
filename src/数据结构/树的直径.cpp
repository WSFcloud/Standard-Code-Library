struct Tree {
    int n;
    vector<vector<int>> tree;
    Tree(int n_) :
        n(n_) {
        tree.resize(n + 1);
    }
    void add(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    int getlen(int root) { // 获取 x 所在树的直径
        map<int, int> dep; // 优化输入为森林时的深度计算，亦可用vector
        auto &t = this->tree;
        auto dfs = [&](this auto &&self, int x, int fa) -> void {
            for (auto y : t[x]) {
                if (y == fa) {
                    continue;
                }
                dep[y] = dep[x] + 1;
                self(y, x);
            }
            if (dep[x] > dep[root]) {
                root = x;
            }
        };
        dfs(root, 0);
        int st = root; // 记录直径端点
        dep.clear();
        dfs(root, 0);
        int ed = root; // 记录直径另一端点
        return dep[root];
    }
};