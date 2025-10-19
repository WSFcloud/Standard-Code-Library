template <typename T>
struct Fenwick {
    int n;
    vector<T> a; // 0 base
    Fenwick(int n_) :
        n(n_), a(n_, T{}) {}
    Fenwick(const vector<T> &v) :
        n(int(v.size())), a(n, T{}) {
        for (int i = 0; i < n; i++) {
            add(i, v[i]);
        }
    }
    // 下标x位置增加值v
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    // 查询区间[0, x)的和
    T sum(int x) {
        T res{};
        for (int i = x; i > 0; i -= i & -i) {
            res = res + a[i - 1];
        }
        return res;
    }
    // 查询区间[l, r)的和
    T range_sum(int l, int r) {
        return sum(r) - sum(l);
    }
    // 查找前缀和小于等于k的最大下标
    int find(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << int(log2(n)); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};