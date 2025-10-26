// 求逆元
ll inv(ll x, ll p);
// 拉格朗日插值
ll lagrange(vector<ll> &x, vector<ll> &y, int n, ll k, ll p) {
    ll s1 = 0, s2 = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        s1 = y[i] % p, s2 = 1;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                s1 = s1 * (k - x[j]) % p;
                s2 = s2 * ((x[i] - x[j] % p) % p) % p;
            }
        }
        ans += s1 * inv(s2, p) % p;
        ans = (ans + p) % p;
    }
    return ans;
}