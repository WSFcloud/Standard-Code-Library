vector<vector<int>> f(n + 1);
void divide(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n / i; j++) {
            f[i * j].push_back(i);
        }
    }
}
