struct Basis {
    const int BASE = 63;
    vector<ll> d, p;
    int cnt, flag;
    Basis() {
        d.resize(BASE + 1);
        p.resize(BASE + 1);
        cnt = flag = 0;
    }
    // 插入 val 到线性基中
    bool insert(ll val) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    d[i] = val;
                    return true;
                }
                val ^= d[i];
            }
        }
        flag = 1; //可以异或出0
        return false;
    }
    // 判断 val 是否能被线性基中的向量异或得到
    bool check(ll val) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    return false;
                }
                val ^= d[i];
            }
        }
        return true;
    }
    // 查询最大异或和
    ll ask_max() {
        ll res = 0;
        for (int i = BASE - 1; i >= 0; i--) {
            if ((res ^ d[i]) > res) {
                res ^= d[i];
            }
        }
        return res;
    }
    // 查询最小异或和
    ll ask_min() {
        if (flag) {
            return 0; // 特判 0
        }
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i]) {
                return d[i];
            }
        }
    }
    // 将基向量转化为最简行阶梯形式，用于支持第k小查询
    void rebuild() {
        for (int i = BASE - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (d[i] & (1ll << j)) {
                    d[i] ^= d[j];
                }
            }
        }
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i]) {
                p[cnt++] = d[i];
            }
        }
    }
    // 查询能被异或得到的第 k 小值, 如不存在则返回 -1
    ll kthquery(ll k) {
        if (flag) {
            k--; // 特判 0, 如果不需要 0, 直接删去
        }
        if (!k) {
            return 0;
        }
        ll res = 0;
        if (k >= (1ll << cnt)) {
            return -1;
        }
        for (int i = BASE - 1; i >= 0; i--) {
            if (k & (1LL << i)) {
                res ^= p[i];
            }
        }
        return res;
    }
    // 合并两个线性基
    void Merge(const Basis &b) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (b.d[i]) {
                insert(b.d[i]);
            }
        }
    }
};