#include <iostream>
#include <array>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using Matrix = array<ull, 65>;

// 重载运算符计算矩阵 $a$ 和矩阵 $b$ 的乘积
Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c{};
    for (int i = 0; i <= 64; i++) {
        for (int j = 0; j <= 64; j++) {
            if (j == 64 ? i == 64 : (a[i] >> j & 1)) {
                c[i] ^= b[j];
            }
        }
    }
    return c;
}
// 重载运算符计算向量 $a$ 与矩阵 $b$ 的乘积
ull operator*(ull a, const Matrix &b) {
    ull c = 0;
    for (int i = 0; i <= 64; i++) {
        if (i == 64 || (a >> i & 1)) {
            c ^= b[i];
        }
    }
    return c;
}

Matrix readMatrix() {
    int m;
    cin >> m;
    Matrix f{};
    for (int i = 0; i < m; i++) {
        int s, o;
        ull A;
        cin >> s >> o >> A;
        if (o == 0) {
            for (int j = 0; j < 64; j++) {
                if (A >> ((j + s) % 64) & 1) {
                    f[64] ^= 1ULL << ((j + s) % 64);
                } else {
                    f[j] ^= 1ULL << ((j + s) % 64);
                }
            }
        } else {
            for (int j = 0; j < 64; j++) {
                if (A >> ((j + s) % 64) & 1) {
                    f[j] ^= 1ULL << ((j + s) % 64);
                }
            }
        }
    }
    ull B;
    cin >> B;
    f[64] ^= B;
    return f;
}