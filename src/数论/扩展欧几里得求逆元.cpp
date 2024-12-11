using ll = long long;

// 扩展欧几里得
ll exgcd(ll a, ll b, ll &x, ll &y);
// 求a在p下的逆元，不存在逆元返回-1
ll inv(ll a, ll p) {
    ll x, y, d = exgcd(a, p, x, y);
    return d == 1 ? (x % p + p) % p : -1;
}