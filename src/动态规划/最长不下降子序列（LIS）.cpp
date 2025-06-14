#include <bits/stdc++.h>
using namespace std;
const int INF = INT_MAX;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> f(n + 1, INF);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int pos = upper_bound(f.begin() + 1, f.begin() + n + 1, a[i]) - f.begin();
        if (f[pos - 1] <= a[i]) {
            f[pos] = a[i];
            ans = max(ans, pos);
        }
    }
    cout << ans << endl;
    return 0;
}
