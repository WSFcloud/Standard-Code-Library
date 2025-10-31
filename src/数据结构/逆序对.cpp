// 需要普通树状数组
template <typename T>
ll inversions(vector<T> &a) {
    auto t = a;
    int n = t.size();
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    auto get = [&](T x) {
        return int(lower_bound(t.begin(), t.end(), x) - t.begin());
    };
    Fenwick<T> f(n);
    ll res = 0;
    for (auto i = n - 1; i >= 0; i--) {
        int id = get(a[i]);
        res += f.sum(id);
        f.add(id, 1);
    }
    return res;
}