#include <bits/stdc++.h>
using namespace std;
using cp = complex<double>;
const double PI = acos(-1.0);

vector<cp> omega[25];
void fft_init(int n) {
    for (int k = 2, d = 0; k <= n; k *= 2, d++) {
        omega[d].resize(k + 1);
        for (int i = 0; i <= k; i++) {
            omega[d][i] = polar(1.0, 2 * PI * i / k);
        }
    }
}
void fft(cp *a, int n, int t) {
    for (int i = 1, j = 0; i < n - 1; i++) {
        int k = n;
        do {
            j ^= (k >>= 1);
        } while (j < k);
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (int k = 1, d = 0; k < n; k *= 2, d++) {
        for (int i = 0; i < n; i += k * 2) {
            for (int j = 0; j < k; j++) {
                cp w = omega[d][t > 0 ? j : k * 2 - j];
                cp u = a[i + j], v = w * a[i + j + k];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
    if (t < 0) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    int len = 1, r = n + m + 1;
    while (len < r) {
        len <<= 1;
    }
    fft_init(len);
    vector<cp> A(len), B(len);
    for (int i = 0; i <= n; i++) {
        int x;
        cin >> x;
        A[i] = x;
    }
    for (int i = 0; i <= m; i++) {
        int x;
        cin >> x;
        B[i] = x;
    }
    fft(A.data(), len, 1);
    fft(B.data(), len, 1);
    for (int i = 0; i < len; i++) {
        A[i] *= B[i];
    }
    fft(A.data(), len, -1);
    for (int i = 0; i < n + m + 1; i++) {
        cout << (int)(A[i].real() + 0.5) << " ";
    }
    cout << endl;
}