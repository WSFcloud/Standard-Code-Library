using ll = long long;

// 普通快速幂
int qpow(ll a, ll b, int p) {
    int res = 1;
    for (; b; b /= 2, a = 1LL * a * a % p) {
        if (b % 2) {
            res = 1LL * res * a % p;
        }
    }
    return res;
}
// 手写乘法快速幂
ll mul(ll a, ll b, ll p) {
    ll c = a * b - ll(1.0L * a * b / p) * p;
    c %= p;
    if (c < 0) {
        c += p;
    }
    return c;
}
ll qpow(ll a, ll b, ll p) {
    ll res = 1;
    for (; b; b /= 2, a = mul(a, a, p)) {
        if (b % 2) {
            res = mul(res, a, p);
        }
    }
    return res;
}