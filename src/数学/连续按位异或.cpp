unsigned xor_n(unsigned n) {
    unsigned t = n & 3;
    if (t & 1) {
        return t / 2u ^ 1;
    }
    return t / 2u ^ n;
}

ll xor_n(ll n) {
    if (n % 4 == 1) {
        return 1;
    } else if (n % 4 == 2) {
        return n + 1;
    } else if (n % 4 == 3) {
        return 0;
    } else {
        return n;
    }
}