#include <iostream>
#include <algorithm>
using namespace std;
using real = long double;
constexpr real EPS = 1E-7;

bool check(int i) {
    // 检查逻辑
}
// 查找满足条件check(mid)的最大值（前驱）
void bsearch_ternary_upper() {
    double lo = 0;
    double hi = 1E12;
    while (hi - lo > max(1.0, lo) * EPS) {
        double mid = (lo + hi) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << lo << "\n";
}
// 查找满足条件check(mid)的最小值（后继）
void bsearch_ternary_lower() {
    double lo = 0;
    double hi = 1E12;
    while (hi - lo > max(1.0, lo) * EPS) {
        double mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    cout << lo << "\n";
}
int main() {
    auto check = [&](double x) {
        // 检查逻辑
    };
    auto target_function = [](real x, real y) {
        // 目标函数
    };
    // 查找 $(px, py)$ 使 $f(px, py)$ 最优
    auto get = [&](const auto &f) {
        real lo = -1E4, hi = 1E4;
        while (hi - lo > 3 * EPS) {
            real x1 = (lo + hi - EPS) / 2;
            real x2 = (lo + hi + EPS) / 2;
            if (f(x1) > f(x2)) {
                lo = x1;
            } else {
                hi = x2;
            }
        }
        return f((lo + hi) / 2);
    };
    real result = get([&](real px) {
        return get([&](real py) {
            return target_function(px, py);
        });
    });
    cout << result << endl;
    return 0;
}