struct Min25 {
    ll n, lim, pcnt, cnt;
    vector<int> vis, primes;
    vector<ll> g, id, pos1, pos2;
    Min25(ll n_) : n(n_), pcnt(0), cnt(0) {
        init();
    }
    void sieve(ll x) {
        vis.assign(x + 1, 0);
        primes.assign(x + 1, 0);
        vis[1] = 1;
        for (int i = 2; i <= x; i++) {
            if (!vis[i]) {
                primes[++pcnt] = i;
            }
            for (int j = 1; j <= pcnt && i * primes[j] <= x; j++) {
                vis[i * primes[j]] = 1;
                if (!(i % primes[j])) {
                    break;
                }
            }
        }
    }
    ll get(ll x) {
        return x <= lim ? pos1[x] : pos2[n / x];
    }
    void init() {
        lim = sqrt(n);
        sieve(lim);
        pos1.assign(lim + 2, 0);
        pos2.assign(lim + 2, 0);
        for (ll i = 1, j; i <= n; i = n / j + 1) {
            j = n / i;
            id.push_back(j);
            g.push_back(j - 1);
            cnt++;
            if (j <= lim)
                pos1[j] = cnt;
            else
                pos2[n / j] = cnt;
        }
        for (int j = 1; j <= pcnt; j++) {
            for (ll i = 1; 1ll * primes[j] * primes[j] <= id[i - 1]; i++) {
                g[i - 1] -= g[get(id[i - 1] / primes[j]) - 1] - (j - 1);
            }
        }
    }
    // 小于等于 n 的质数个数
    ll query() {
        return g[0];
    }
};