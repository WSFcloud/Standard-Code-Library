template <class T>
struct MinCostFlow {
    struct edge {
        int to;
        T cap;  // 边的剩余容量
        T cost; // 边的单位流量费用
        edge(int to_, T cap_, T cost_) :
            to(to_), cap(cap_), cost(cost_) {}
    };
    int n;
    vector<edge> edges;
    vector<vector<int>> graph;
    vector<T> h, dis;
    vector<int> pre;
    MinCostFlow(int n_) {
        n = n_;
        edges.clear();
        graph.assign(n, {});
    }
    // 寻找最短增广路
    bool dijkstra(int s, int t) {
        dis.assign(n, numeric_limits<T>::max());
        pre.assign(n, -1);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
        dis[s] = 0;
        q.emplace(0, s);
        while (!q.empty()) {
            T d = q.top().first;
            int u = q.top().second;
            q.pop();
            if (dis[u] != d) {
                continue;
            }
            for (int i : graph[u]) {
                int v = edges[i].to;
                T cap = edges[i].cap;
                T cost = edges[i].cost;
                if (cap > 0 && dis[v] > d + h[u] - h[v] + cost) {
                    dis[v] = d + h[u] - h[v] + cost;
                    pre[v] = i;
                    q.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != numeric_limits<T>::max();
    }
    // 添加一条从 u 到 v 容量为 cap，费用为 cost 的边
    void add(int u, int v, T cap, T cost) {
        // 正向边容量为 cap，费用为 cost
        graph[u].push_back(edges.size());
        edges.emplace_back(v, cap, cost);
        // 反向边容量为 0，费用为 -cost
        graph[v].push_back(edges.size());
        edges.emplace_back(u, 0, -cost);
    }
    // 计算从 s 到 t 的最小费用最大流
    pair<T, T> min_cost_flow(int s, int t) {
        T flow = 0;
        T cost = 0;
        h.assign(n, 0);
        while (dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) {
                h[i] += dis[i];
            }
            T aug = numeric_limits<T>::max();
            for (int i = t; i != s; i = edges[pre[i] ^ 1].to) {
                aug = min(aug, edges[pre[i]].cap);
            }
            for (int i = t; i != s; i = edges[pre[i] ^ 1].to) {
                edges[pre[i]].cap -= aug;
                edges[pre[i] ^ 1].cap += aug;
            }
            flow += aug;
            cost += aug * h[t];
        }
        return make_pair(flow, cost);
    }
};