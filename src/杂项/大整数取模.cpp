constexpr int mod = 998244353;
int f(string &s) {
    int res = 0;
    for (auto &c : s) {
        res = res * 10 % mod + (c - '0');
        res %= mod;
    }
    return res;
};