// 求逆元
ll inv(ll x, ll p);
vector<int> batch_inv(vector<int> &a, int p) { // base 1
    int n = a.size() - 1;
    vector<int> s(n + 1), res(n + 1);
    s[0] = 1;
    for (auto i = 1; i <= n; i++) {
        s[i] = 1ll * s[i - 1] * a[i] % p;
    }
    ll sii = inv(s[n], p);
    for (auto i = n; i >= 1; i--) {
        res[i] = 1ll * s[i - 1] * sii % p;
        sii = 1ll * a[i] * sii % p;
    }
    return res;
}