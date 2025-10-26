// 快速幂
int qpow(ll a, ll b, int p);
// 求逆元
ll inv(ll x, ll p) {
    return qpow(x, p - 2, p);
}