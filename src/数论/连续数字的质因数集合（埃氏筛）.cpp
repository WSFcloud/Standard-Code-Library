vector<vector<int>> pfac;
void fac(int n) {
    pfac.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!pfac[i].empty()) {
            continue;
        }
        for (int j = i; j <= n; j += i) {
            pfac[j].push_back(i);
        }
    }
}