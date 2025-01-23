#include <vector>
using namespace std;

template <typename T>
struct Fenwick {
    int n;
    vector<T> a; // 0 base
    Fenwick(int n_ = 0) {
        n = n_;
        a.assign(n, T{});
    }
    // 下标x位置增加值v
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    // 查询[l, r)区间的和
    T range_sum(int l, int r) {
        return sum(r) - sum(l);
    }
    // 查找前缀和小于等于k的最大下标
    int find(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x - 1;
    }
};