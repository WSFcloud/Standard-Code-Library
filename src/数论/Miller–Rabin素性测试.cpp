using ll = long long;

bool check(ll n, ll b) { // b: base
    ll a = n - 1;
    int k = 0;
    while (a % 2 == 0) {
        a /= 2;
        k++;
    }
    ll t = qpow(b, a, n); // 这里的快速幂函数需要写O(1)快速乘
    if (t == 1 || t == n - 1) {
        return true;
    }
    while (k--) {
        t = mul(t, t, n); // mul是O(1)快速乘函数
        if (t == n - 1) {
            return true;
        }
    }
    return false;
}
bool Miller_Rabin(ll n) {
    if (n == 1) {
        return false;
    }
    if (n == 2)
        return true;
    if (n % 2 == 0) {
        return false;
    }
    // int范围内只需要检查 {2, 7, 61}
    // ll范围内只需要检查 {2, 325, 9375, 28178, 450775, 9780504, 1795265022}
    for (int i : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (i >= n) {
            break;
        }
        if (!check(n, i)) {
            return false;
        }
    }
    return true;
}