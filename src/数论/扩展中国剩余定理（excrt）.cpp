ll excrt(ll b[], ll a[], ll n) {
    ll x = 0, y = 0, d = 0;
    ll M = a[0], R = b[0];
    for (register int i = 1; i < n; i++) {
        d = exgcd(M, a[i], x, y);
        if ((R - b[i]) % d)
            return -1;
        x = (R - b[i]) / d * x % a[i];
        R -= M * x;
        M = M / d * a[i];
        R %= M;
    }
    return (R % M + M) % M;
}