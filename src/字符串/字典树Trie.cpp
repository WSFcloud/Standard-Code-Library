int trie[N][2];
int cnt[N][2];
int tot = 0;
int newNode() {
    int x = ++tot;
    trie[x][0] = trie[x][1] = 0;
    cnt[x][0] = cnt[x][1] = 0;
    return x;
}
// 插入值和其下标
void add(int x, int d, int t = 1) {
    int p = 1;
    cnt[p][d] += t;
    for (int i = 29; i >= 0; i--) {
        int u = x >> i & 1;
        if (!trie[p][u]) {
            trie[p][u] = newNode();
        }
        p = trie[p][u];
        cnt[p][d] += t;
    }
}
// 查询满足 x ^ a <= b 的 x 的最小下标
int query(int x, int d) {
    int p = 1;
    if (!cnt[p][d]) {
        return 0;
    }
    int ans = 0;
    for (int i = 29; i >= 0; i--) {
        int u = x >> i & 1;
        if (cnt[trie[p][u ^ 1]][d]) {
            ans |= 1 << i;
            p = trie[p][u ^ 1];
        } else {
            p = trie[p][u];
        }
    }
    return ans;
}