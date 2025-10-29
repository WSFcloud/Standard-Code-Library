struct ST {
    int n, k;
    vector<int> a; // 0 base
    vector<vector<int>> maxst, minst;
    ST(int n_, vector<int> &data) :
        n(n_), k(__lg(n_)), a(data) {
        a.resize(n);
        maxst.resize(k + 1, vector<int>(n));
        minst.resize(k + 1, vector<int>(n));
        for (int i = 0; i < n; i++) {
            a[i] = data[i];
        }
        for (int i = 0; i < n; i++) {
            maxst[0][i] = a[i];
            minst[0][i] = a[i];
        }
        for (int i = 0, t = 1; i < k; i++, t <<= 1) {
            const int T = n - (t << 1);
            for (int j = 0; j <= T; j++) {
                maxst[i + 1][j] = max(maxst[i][j], maxst[i][j + t]);
                minst[i + 1][j] = min(minst[i][j], minst[i][j + t]);
            }
        }
    }
    // 查询区间 [l, r) 的最大值
    int query_max(int l, int r) {
        int len = r - l;
        int p = __lg(len);
        return max(maxst[p][l], maxst[p][r - (1 << p)]);
    }
    // 查询区间 [l, r) 的最小值
    int query_min(int l, int r) {
        int len = r - l;
        int p = __lg(len);
        return min(minst[p][l], minst[p][r - (1 << p)]);
    }
};