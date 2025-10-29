template <typename T>
struct Flow {
    const int n;
    const T inf = numeric_limits<T>::max();
    struct edge {
        int to;
        T w;
        edge(int to, T w) :
            to(to), w(w) {}
    };
    vector<edge> edges;
    vector<vector<int>> graph;
    vector<int> cur; // 当前弧优化数组，记录每个节点当前访问到哪条边
    vector<int> d;   // 层次深度数组，用于 BFS 分层
    Flow(int n_) :
        n(n_ + 1), graph(n_ + 1) {}
    // 添加一条从 u 到 v 容量为 c 的边，同时添加反向边
    void add(int u, int v, T c) {
        // 正向边索引为偶数
        graph[u].push_back(edges.size());
        edges.emplace_back(v, c);
        // 反向边索引为奇数，初始容量为 0
        graph[v].push_back(edges.size());
        edges.emplace_back(u, 0);
    }
    // 计算每个节点到源点的最短距离
    bool bfs(int s, int t) {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            for (auto it : graph[x]) {
                auto [y, w] = edges[it];
                if (w && d[y] == -1) {
                    d[y] = d[x] + 1;
                    if (y == t) {
                        return true;
                    }
                    q.push(y);
                }
            }
        }
        return false;
    }
    // 在层次图上进行多路增广
    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < graph[u].size(); i++) {
            auto j = graph[u][i];
            auto &[v, c] = edges[j];
            auto &[u, rc] = edges[j ^ 1];
            if (c && d[v] == d[u] + 1) {
                auto a = dfs(v, t, min(r, c));
                c -= a;
                rc += a;
                r -= a;
                if (!r) {
                    return f;
                }
            }
        }
        return f - r;
    }
    // 计算从 s 到 t 的最大流
    T max_flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, inf);
        }
        return ans;
    }
};