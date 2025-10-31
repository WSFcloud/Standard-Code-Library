template <typename T>
struct Fenwick {
    int n;
    vector<T> a; // 1-based
    Fenwick(int n_) :
        n(n_), a(n_ + 1, T{}) {}
    // 更新位置 x 的值为 max(a[x], v)
    void update(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i] = max(a[i], v);
        }
    }
    // 查询区间 [0, x] 的最大值
    T query(int x) {
        T res{};
        for (int i = x + 1; i > 0; i -= i & -i) {
            res = max(res, a[i]);
        }
        return res;
    }
};