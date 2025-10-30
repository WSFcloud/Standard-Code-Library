struct Min25 {
    vector<int> primes, minp, id1, id2;
    vector<ll> g, sum, a;
    int n, pcnt, m;
    ll T;
    Min25(int n_) :
        n(n_) {
        init();
    }
    inline int ID(ll x) const {
        return x <= T ? id1[x] : id2[n / x];
    }
    inline ll calc(ll x) const {
        return x * (x + 1) / 2 - 1;
    }
    inline ll f(ll x) const {
        return x;
    }
    inline void init() {
        T = sqrt(n + 0.5);
        pcnt = 0;
        m = 0;
        pcnt = 0;
        minp.assign(T + 1, 0);
        primes.assign(T + 1, 0);
        sum.assign(T + 1, 0);
        id1.assign(T + 1, 0);
        id2.assign(T + 1, 0);
        for (int i = 2; i <= T; i++) {
            if (!minp[i]) {
                primes[++pcnt] = i;
                sum[pcnt] = sum[pcnt - 1] + i;
            }
            for (int j = 1; j <= pcnt && (ll)i * primes[j] <= T; j++) {
                minp[i * primes[j]] = 1;
                if (i % primes[j] == 0) {
                    break;
                }
            }
        }
        for (ll l = 1; l <= n; l = n / (n / l) + 1) {
            a.push_back(n / l);
            m++;
        }
        g.resize(m + 1);
        for (int i = 1; i <= m; i++) {
            ll x = a[i - 1];
            if (x <= T) {
                id1[x] = i;
            } else {
                id2[n / x] = i;
            }
            g[i] = calc(x);
        }
        for (int i = 1; i <= pcnt; i++) {
            for (int j = 1; j <= m && (ll)primes[i] * primes[i] <= a[j - 1]; j++) {
                g[j] = g[j] - (ll)primes[i] * (g[ID(a[j - 1] / primes[i])] - sum[i - 1]);
            }
        }
    }
    ll query() {
        return g[ID(n)];
    }
};