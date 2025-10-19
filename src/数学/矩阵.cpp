template <typename T>
struct Matrix {
    int row, col;
    vector<vector<T>> mat;
    Matrix(int n, int m) :
        row(n), col(m), mat(n, vector<T>(m, T(0))) {}
    Matrix(const vector<vector<T>> &arr) :
        mat(arr) {
        row = mat.size();
        col = row > 0 ? mat[0].size() : 0;
    }
    vector<T> &operator[](int i) { return mat[i]; }
    const vector<T> &operator[](int i) const { return mat[i]; }

    // 矩阵加法
    Matrix operator+(const Matrix &a) const {
        Matrix res(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                res[i][j] = mat[i][j] + a[i][j];
            }
        }
        return res;
    }
    // 矩阵减法
    Matrix operator-(const Matrix &a) const {
        Matrix res(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                res[i][j] = mat[i][j] - a[i][j];
            }
        }
        return res;
    }
    // 标量乘法（右乘）
    Matrix operator*(T scalar) const {
        Matrix res(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                res[i][j] = mat[i][j] * scalar;
            }
        }
        return res;
    }
    // 标量乘法（左乘）
    friend Matrix operator*(T scalar, const Matrix &mat) {
        return mat * scalar;
    }
    // 矩阵乘法
    Matrix operator*(const Matrix &a) const {
        Matrix res(row, a.col);
        for (int i = 0; i < row; i++) {
            for (int k = 0; k < col; k++) {
                for (int j = 0; j < a.col; j++)
                    res[i][j] += mat[i][k] * a[k][j];
            }
        }
        return res;
    }
    // 矩阵快速幂
    Matrix mat_pow(ll k) const {
        Matrix res = identity(row);
        Matrix base = *this;
        while (k) {
            if (k & 1) {
                res = res * base;
            }
            base = base * base;
            k >>= 1;
        }
        return res;
    }
    // 转置
    Matrix transpose() const {
        Matrix res(col, row);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                res[j][i] = mat[i][j];
            }
        }
        return res;
    }
    // 矩阵求逆
    tuple<bool, Matrix> inverse() const {
        Matrix a = *this;
        Matrix invm = identity(row);
        for (int i = 0; i < row; i++) {
            int pivot = i;
            for (int j = i + 1; j < row; j++) {
                if (abs(a[j][i]) > abs(a[pivot][i])) {
                    pivot = j;
                }
            }
            if (abs(a[pivot][i]) < 1e-10) {
                return {false, Matrix(0, 0)};
            }
            if (pivot != i) {
                swap(a[i], a[pivot]);
                swap(invm[i], invm[pivot]);
            }
            T divisor = a[i][i];
            for (int j = 0; j < row; j++) {
                a[i][j] /= divisor;
                invm[i][j] /= divisor;
                // a[i][j] = a[i][j] * inv(divisor, mod) % mod;
                // invm[i][j] = invm[i][j] * inv(divisor, mod) % mod;
            }
            for (int j = 0; j < row; j++) {
                if (j == i) {
                    continue;
                }
                T factor = a[j][i];
                for (int k = 0; k < row; k++) {
                    a[j][k] -= factor * a[i][k];
                    invm[j][k] -= factor * invm[i][k];
                    // a[j][k] = ((a[j][k] % mod) - factor * a[i][k] % mod + mod) % mod;
                    // invm[j][k] = ((invm[j][k] % mod) - factor * invm[i][k] % mod + mod) % mod;
                }
            }
        }
        return {true, invm};
    }
    // 行列式计算（高斯消元法）
    T determinant() const {
        Matrix a = *this;
        T det = T(1);
        for (int i = 0; i < row; i++) {
            int pivot = i;
            for (int j = i; j < row; j++) {
                if (a[j][i] != T(0)) {
                    pivot = j;
                    break;
                }
            }
            if (a[pivot][i] == T(0)) {
                return T(0);
            }
            if (i != pivot) {
                swap(a[i], a[pivot]);
                det = -det;
            }
            det *= a[i][i];
            T inv = T(1) / a[i][i];
            for (int j = i + 1; j < row; j++) {
                T factor = a[j][i] * inv;
                for (int k = i; k < row; k++) {
                    a[j][k] -= factor * a[i][k];
                }
            }
        }
        return det;
    }
    // 单位矩阵
    static Matrix identity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; i++) {
            res[i][i] = T(1);
        }
        return res;
    }
    // 全零矩阵
    static Matrix zeros(int n, int m) {
        return Matrix(n, m);
    }
    // 全一矩阵
    static Matrix ones(int n, int m) {
        Matrix res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[i][j] = T(1);
            }
        }
        return res;
    }
};