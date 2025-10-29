struct info {
    int l, r;
    mutable ll v;
    info(int l_, int r_ = -1, ll v_ = 0) : l(l_), r(r_), v(v_) {}
    bool operator<(const info &p) const {
        return l < p.l;
    }
};
struct ODT {
    int n;
    set<info> s;
    ODT(int n_, ll init_v) : n(n_) {
        s.insert(info(0, n, init_v));
    }
    // 在 pos 位置分割区间，返回包含 pos 的新区间迭代器
    auto split(int pos) {
        if (pos <= 0) {
            auto it = s.begin();
            return it;
        }
        if (pos >= n) {
            return s.end();
        }
        auto it = s.lower_bound(info(pos));
        if (it != s.end() && it->l == pos) {
            return it;
        }
        it--;
        int L = it->l, R = it->r;
        ll V = it->v;
        // 移除旧区间并插入拆分后的两个区间
        s.erase(it);
        s.insert(info(L, pos, V));
        auto inserted = s.insert(info(pos, R, V));
        return inserted.first;
    }
    // 将区间 [l, r) 的所有	值设为 x
    void assign(int l, int r, ll x) {
        auto itr = split(r);
        auto itl = split(l);
        s.erase(itl, itr);
        s.insert(info(l, r, x));
    }
    // 将区间 [l, r) 的所有值加上 x
    void add(int l, int r, ll x) {
        auto itr = split(r);
        auto itl = split(l);
        for (auto it = itl; it != itr; it++) {
            it->v += x;
        }
    }
    // 查询区间 [l, r) 的第 k 小值，k 从 1 开始
    ll kth(int l, int r, int k) {
        vector<pair<ll, int>> a;
        auto itr = split(r);
        auto itl = split(l);
        for (auto it = itl; it != itr; it++) {
            a.push_back(pair<ll, int>(it->v, it->r - it->l));
        }
        sort(a.begin(), a.end(), [](const pair<ll, int> &x, const pair<ll, int> &y) {
            if (x.first != y.first) {
                return x.first < y.first;
            }
            return false;
        });
        for (auto &pr : a) {
            k -= pr.second;
            if (k <= 0) {
                return pr.first;
            }
        }
        return -1;
    }
    // 计算区间 [l, r) 内所有值的 x 次方之和 mod p
    ll power_sum(int l, int r, int x, int p) {
        auto itr = split(r);
        auto itl = split(l);
        ll res = 0;
        for (auto it = itl; it != itr; it++) {
            int len = it->r - it->l;
            res = (res + 1ll * qpow(it->v, x, p) * len % p) % p;
        }
        if (res < 0) {
            res += p;
        }
        return res;
    }
};