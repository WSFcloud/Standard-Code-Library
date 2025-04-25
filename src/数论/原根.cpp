// 分解质因数
vector<int> split(int n) {
    vector<int> a;
    int i = 2;
    while (i * i <= n) {
        if (n % i == 0) {
            a.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
        i++;
    }
    if (n > 1) {
        a.push_back(n);
    }
    return a;
}
// 判断g是否是原根，需要调用快速幂
bool judge(int g, int p, const vector<int> &factors) {
    for (int d : factors) {
        if (qpow(g, (p - 1) / d, p) == 1) {
            return false;
        }
    }
    return true;
}
// 寻找原根
int getg(int p) {
    vector<int> d = split(p - 1);
    int g = 2;
    while (!judge(g, p, d)) {
        g++;
    }
    return g;
}