vector<int> primes, isprime, phi;
void eulers_totient_function(int n) {
    isprime.resize(n + 1, 1);
    isprime[0] = 0, isprime[1] = 0;
    phi.resize(n + 1);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            isprime[i * p] = false;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
}