#include <iostream>
using namespace std;
using ll = long long;

bool check(int i) {
    // 检查逻辑
}
// 查找满足条件check(mid)的最大值（前驱）
void bsearch_upper() {
    int lo = 1, hi = 1E9;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    cout << lo << "\n";
}
// 查找满足条件check(mid)的最小值（后继）
void bsearch_lower() {
    int lo = 1, hi = 1E9;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << lo << "\n";
}