bool Miller_Rabin(ll n) {
    if (n < 2) {
        return false;
    }
    static constexpr int A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    int s = __builtin_ctzll(n - 1);
    ll d = (n - 1) >> s;
    for (auto a : A) {
        if (a == n) {
            return true;
        }
        ll x = qpow(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool ok = false;
        for (int i = 0; i < s - 1; ++i) {
            x = mul(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            return false;
        }
    }
    return true;
}