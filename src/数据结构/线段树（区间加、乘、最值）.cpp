constexpr ll mod = 998244353;
struct Info {
    ll sum;
    ll maxv = 0;
    Info operator+(const Info &info) const {
        return {(sum + info.sum) % mod, max(maxv, info.maxv)};
    }
};
// 线段为 0 base，树为 1 base
struct SegmentTree {
    int n;
    vector<ll> addtag, multag;
    vector<Info> info;
    SegmentTree(int n_) :
        n(n_), addtag(4 * n), multag(4 * n, 1), info(4 * n) {}
    // 更新节点数据
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void make_addtag(int p, int l, int r, ll v) {
        addtag[p] = (addtag[p] + v) % mod;
        info[p].sum = (info[p].sum + v * (r - l)) % mod;
        info[p].maxv += v;
    }
    void make_multag(int p, ll v) {
        addtag[p] = addtag[p] * v % mod;
        multag[p] = multag[p] * v % mod;
        info[p].sum = info[p].sum * v % mod;
        info[p].maxv *= v;
    }
    // 将节点 p 的懒标记向子节点下传
    void push(int p, int l, int r) {
        int mid = (l + r) / 2;
        make_multag(2 * p, multag[p]);
        make_multag(2 * p + 1, multag[p]);
        make_addtag(2 * p, l, mid, addtag[p]);
        make_addtag(2 * p + 1, mid, r, addtag[p]);
        multag[p] = 1;
        addtag[p] = 0;
    }
    Info query(int p, int l, int r, int x, int y) {
        if (r <= x || y <= l) {
            return {};
        }
        if (x <= l && r <= y) {
            return info[p];
        }
        int mid = (l + r) / 2;
        push(p, l, r);
        return query(2 * p, l, mid, x, y) + query(2 * p + 1, mid, r, x, y);
    }
    // 查询 [x, y) 区间的数据信息
    Info query(int x, int y) {
        return query(1, 0, n, x, y);
    }
    void range_add(int p, int l, int r, int x, int y, ll v) {
        if (r <= x || y <= l) {
            return;
        }
        if (x <= l && r <= y) {
            return make_addtag(p, l, r, v);
        }
        int mid = (l + r) / 2;
        push(p, l, r);
        range_add(2 * p, l, mid, x, y, v);
        range_add(2 * p + 1, mid, r, x, y, v);
        pull(p);
    }
    // 将值 v 加到 [x, y) 区间
    void range_add(int x, int y, ll v) {
        range_add(1, 0, n, x, y, v);
    }
    void range_mul(int p, int l, int r, int x, int y, ll v) {
        if (r <= x || y <= l) {
            return;
        }
        if (x <= l && r <= y) {
            return make_multag(p, v);
        }
        int mid = (l + r) / 2;
        push(p, l, r);
        range_mul(2 * p, l, mid, x, y, v);
        range_mul(2 * p + 1, mid, r, x, y, v);
        pull(p);
    }
    // 将值 v 乘到 [x, y) 区间
    void range_mul(int x, int y, ll v) {
        range_mul(1, 0, n, x, y, v);
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p, l, r);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    // 修改位置 x 的值为 v
    void modify(int x, const Info &v) {
        modify(1, 0, n, x, v);
    }
    void build(int p, int l, int r, const vector<ll> &a) {
        if (r - l == 1) {
            info[p] = {a[l], a[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(2 * p, l, mid, a);
        build(2 * p + 1, mid, r, a);
        pull(p);
    }
    // 在给定数组 a 上建立线段树
    void build(const vector<ll> &a) {
        build(1, 0, n, a);
    }
};