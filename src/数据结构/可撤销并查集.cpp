#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
using namespace std;

struct DSU {
    vector<int> f, siz;        // 0 base
    vector<array<int, 2>> his; // 0 base
    DSU(int n) :
        f(n + 1), siz(n + 1, 1) {
        iota(f.begin(), f.end(), 0);
    }
    int find(int x) {
        while (f[x] != x) {
            x = f[x];
        }
        return x;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            swap(x, y);
        }
        his.push_back({x, y});
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int time() {
        return his.size();
    }
    // 撤销到指定时间点
    void revert(int time) {
        while (his.size() > time) {
            auto [x, y] = his.back();
            his.pop_back();
            f[y] = y;
            siz[x] -= siz[y];
        }
    }
};