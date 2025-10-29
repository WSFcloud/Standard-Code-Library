struct DSU {
    vector<int> f, siz; // 父节点、集合大小
    vector<int> ecnt;   // 每个集合的边数量
    vector<bool> isc;   // 每个集合是否有环
    DSU(int n) : f(n), siz(n, 1), ecnt(n, 0), isc(n, false) {
        iota(f.begin(), f.end(), 0);
    }
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    // 判断连通性
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    // 合并 x, y 所在集合
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) { // 已在同一集合，增加一条边
            ecnt[x]++;
            isc[x] = true;
            return false;
        }
        if (siz[x] < siz[y]) {
            swap(x, y);
        }
        f[y] = x;
        siz[x] += siz[y];
        ecnt[x] += ecnt[y] + 1;
        isc[x] = isc[x] || isc[y];
        return true;
    }
    // 返回集合内点数量
    int size(int x) {
        return siz[find(x)];
    }
    // 返回集合内边数量
    int edges(int x) {
        return ecnt[find(x)];
    }
    // 判断集合内是否存在环
    bool is_cycle(int x) {
        return isc[find(x)];
    }
};