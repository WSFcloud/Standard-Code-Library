void GospersHack(int k, int n) {
    int cur = (1 << k) - 1, limit = (1 << n);
    while (cur < limit) {
        // do something
        int lb = cur & -cur, r = cur + lb;
        cur = (((r ^ cur) >> 2) / lb) | r;
    }
}