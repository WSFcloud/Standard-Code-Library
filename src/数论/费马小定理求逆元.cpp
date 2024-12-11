using ll = long long;

// 快速幂
int power(int a, ll b, int p);
// 求逆元
ll inv(ll x, ll p) {
    return power(x, p - 2, p);
}