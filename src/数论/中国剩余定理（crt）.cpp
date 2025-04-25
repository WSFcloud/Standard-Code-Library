ll crt(int len, ll *a, ll *p) {
    ll M = 1, x = 0;
    for (int i = 1; i <= len; i++) {
        M = M * p[i];
    }
    for (int i = 1; i <= len; i++) {
        ll m = M / p[i], b, y;
        exgcd(m, p[i], b, y); // b * m mod p[i] = 1
        x = (x + a[i] * m * b % M) % M;
    }
    return (x % M + M) % M;
}