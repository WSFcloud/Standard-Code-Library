// 按位或
void FWT_or(vector<int> &a, int t, int p) {
    int n = a.size();
    for (int k = 2; k <= n; k *= 2) {
        for (int i = 0; i < n; i += k) {
            for (int j = 0; j < k / 2; j++) {
                if (t > 0) {
                    a[i + j + k / 2] = (a[i + j + k / 2] + a[i + j]) % p;
                } else {
                    a[i + j + k / 2] = (a[i + j + k / 2] - a[i + j] + p) % p;
                }
            }
        }
    }
}
// 按位与
void FWT_and(vector<int> &a, int t, int p) {
    int n = a.size();
    for (int k = 2; k <= n; k *= 2) {
        for (int i = 0; i < n; i += k) {
            for (int j = 0; j < k / 2; j++) {
                if (t > 0) {
                    a[i + j] = (a[i + j] + a[i + j + k / 2]) % p;
                } else {
                    a[i + j] = (a[i + j] - a[i + j + k / 2] + p) % p;
                }
            }
        }
    }
}
// 按位异或
void FWT_xor(vector<int> &a, int t, int p) {
    int n = a.size();
    for (int k = 2; k <= n; k *= 2) {
        for (int i = 0; i < n; i += k) {
            for (int j = 0; j < k / 2; j++) {
                int x = a[i + j], y = a[i + j + k / 2];
                a[i + j] = (x + y) % p;
                a[i + j + k / 2] = (x - y + p) % p;
            }
        }
    }
    if (t < 0) {
        int inv = qpow(n % p, p - 2, p); // n 的逆元，在不取模时需要用每层除以 2 代替
        for (int i = 0; i < n; i++) {
            a[i] = 1ll * a[i] * inv % p;
        }
    }
}