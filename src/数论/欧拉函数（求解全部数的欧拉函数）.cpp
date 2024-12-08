#include <vector>
#include <algorithm>
using namespace std;
constexpr int N = 1E7;
constexpr int P = 1000003;
bool isprime[N + 1];
int phi[N + 1];
vector<int> primes;

void eulers_totient_function() {
    fill(isprime + 2, isprime + N + 1, true);
    phi[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : primes) {
            if (i * p > N) {
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