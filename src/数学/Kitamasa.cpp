int kitamasa(const vector<int> &coef, const vector<int> &a, ll n, ll p) {
    if (n < ll(a.size())) {
        return a[n] % p;
    }
    int k = coef.size();
    if (k == 0) {
        return 0;
    }
    if (k == 1) {
        return 1ll * a[0] * qpow(coef[0], n, p) % p;
    }
    // 已知 f(n) 的各项系数为 A，f(m) 的各项系数为 B
    // 计算并返回 f(n+m) 的各项系数 C
    auto compose = [&](const vector<int> &A, vector<int> B, ll p) -> vector<int> {
        vector<int> C(k);
        for (int v : A) {
            for (int j = 0; j < k; j++) {
                C[j] = (C[j] + 1ll * v * B[j] % p) % p;
            }
            int bk1 = B.back();
            for (int i = k - 1; i > 0; i--) {
                B[i] = (B[i - 1] + 1ll * bk1 * coef[i] % p) % p;
            }
            B[0] = 1 * bk1 * coef[0] % p;
        }
        return C;
    };

    // f(n) = res_c[k-1] * a[k-1] + res_c[k-2] * a[k-2] + ... + res_c[0] * a[0]
    vector<int> res_c(k), c(k);
    res_c[0] = c[1] = 1;
    for (; n > 0; n /= 2) {
        if (n % 2) {
            res_c = compose(c, std::move(res_c), p);
        }
        c = compose(c, c, p);
    }
    ll res = 0;
    for (int i = 0; i < k; i++) {
        res = (res + 1ll * res_c[i] * a[i] % p) % p;
    }
    return (res + p) % p;
}