// 需要使用Miller-Rabin、O(1)快速乘
ll Pollards_Rho(ll n) {
    // assert(n > 1);
    if (Miller_Rabin(n)) {
        return n;
    }
    // 注意这里rand函数需要重定义一下
    ll c = rand() % (n - 2) + 1, i = 1, k = 2, x = rand() % (n - 3) + 2, u = 2;
    while (true) {
        i++;
        x = (mul(x, x, n) + c) % n; // mul是O(1)快速乘函数
        ll g = gcd((u - x + n) % n, n);
        if (g > 1 && g < n) {
            return g;
        }
        if (u == x) {
            return 0; // 失败, 需要重新调用
        }
        if (i == k) {
            u = x;
            k *= 2;
        }
    }
}
void rec(ll n, vector<ll> &v) {
    if (n == 1) {
        return;
    }
    ll p;
    do {
        p = Pollards_Rho(n);
    } while (!p); // p是任意一个非平凡因子
    if (p == n) {
        v.push_back(p); // 说明n本身就是质数
        return;
    }
    rec(p, v); // 递归分解两半
    rec(n / p, v);
}
// v用于存分解出来的质因子, 重复的会放多个
void factorize(ll n, vector<ll> &v) {
    for (int i : {2, 3, 5, 7, 11, 13, 17, 19})
        while (n % i == 0) {
            v.push_back(i);
            n /= i;
        }
    rec(n, v);
    sort(v.begin(), v.end()); // 从小到大排序后返回
}