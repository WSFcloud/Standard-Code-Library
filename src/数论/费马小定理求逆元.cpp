using ll = long long;
constexpr ll mod = 2147483647;

// 快速幂
int power(int a, ll b, int p);
// 求逆元
ll inv(ll x) {
    return power(x, mod - 2, mod);
}