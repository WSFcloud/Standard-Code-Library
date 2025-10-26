using ll = long long;
using i128 = __int128;

// 向上取整
ll ceilDiv(ll n, ll m) {
    if (n >= 0) {
        return (n + m - 1) / m;
    } else {
        return n / m;
    }
}
// 向下取整
ll floorDiv(ll n, ll m) {
    if (n >= 0) {
        return n / m;
    } else {
        return (n - m + 1) / m;
    }
}
// 最大值赋值
template <class T>
void chmax(T &a, T b) {
    if (a < b) {
        a = b;
    }
}
// 最大公约数
i128 gcd(i128 a, i128 b) {
    return b ? gcd(b, a % b) : a;
}
// 精确开平方
ll accurate_sqrt(ll n) {
    ll s = sqrt(n);
    while (s * s > n) {
        s--;
    }
    while ((s + 1) * (s + 1) <= n) {
        s++;
    }
    return s;
}
// 求 $\log_{a}b$
int logi(int a, int b) {
    int t = 0;
    ll v = 1;
    while (v < b) {
        v *= a;
        t++;
    }
    return t;
}