using ull = unsigned long long;
// Test 1: 循环
void test_xor_loop() {
    int a = 1000000000, b = 1;
    while (a) {
        b ^= a;
        a--;
    }
    printf("%d\n", b);
}
// Test 7: 整数除法和取模
void test_modular_multiplication() {
    const ull P = 1000000007;
    const int MX = 100000000;
    ull ans = 1;
    for (int i = 1; i < MX; i++) {
        ans = ans * i % P;
    }
    printf("%llu\n", ans);
}
// Test 8: 浮点数运算
void test_floating_point() {
    const int MX = 20000000;
    double ans = 0.61234567898765, t = 1, s = 0;
    for (int i = 1; i < MX; i++) {
        s += (t *= ans);
    }
    printf("%f\n", s);
}