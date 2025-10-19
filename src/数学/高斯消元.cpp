template <typename T, int N>
pair<bool, vector<T>> solve_linear_system(Matrix<T, N, N> &A, array<T, N> &b) {
    const T eps = 1e-9; // 仅在浮点数时适用
    vector<T> x(N, T(0));
    for (int i = 0; i < N; i++) {
        int pivot = i;
        for (int j = i + 1; j < N; j++) {
            if (abs(A[j][i]) > abs(A[pivot][i])) {
                pivot = j;
            }
        }
        if (abs(A[pivot][i]) < eps) {
            // 主元为 0，说明可能无解或多解
            return {false, {}};
        }
        if (pivot != i) {
            swap(A[i], A[pivot]);
            swap(b[i], b[pivot]);
        }
        T div = A[i][i];
        for (int j = i; j < N; j++) {
            A[i][j] /= div;
        }
        b[i] /= div;
        for (int j = 0; j < N; j++) {
            if (j == i) {
                continue;
            }
            T factor = A[j][i];
            for (int k = i; k < N; k++) {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }
    for (int i = 0; i < N; i++) {
        x[i] = b[i];
    }
    return {true, x};
}