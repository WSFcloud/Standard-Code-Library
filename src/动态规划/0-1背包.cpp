#include <vector>
using namespace std;
int N = 10000, V = 500;

auto dp = [&]() {
    for (int i = 1; i <= N; i++) {
        for (int j = V; j >= c[i]; j--) {
            f[j] = max(f[j], f[j - c[i]] + w[i]);
        }
    }
};