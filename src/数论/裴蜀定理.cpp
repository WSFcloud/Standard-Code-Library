int ans = 0;
vector<int> a(n + 1);
for (auto i = 1; i <= n; i++) {
    if (a[i] < 0) {
        a[i] *= -1;
    }
    ans = gcd(ans, a);
}