constexpr double EPS = 1e-9;
template <typename T>
pair<int, vector<T>> solve_linear_system(Matrix<T> &a, vector<T> &b) {
    int n = a.row;
    int m = a.col;
    Matrix<T> am(n, m + 1); // 增广矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; ++j) {
            am[i][j] = a[i][j];
        }
        am[i][m] = b[i];
    }
    int rank = 0;
    int pivot = 0; // 当前处理的主元行
    for (int j = 0; j < m && pivot < n; ++j) {
        // 寻找主元
        int max_row = pivot;
        for (int i = pivot + 1; i < n; ++i) {
            if (abs(am[i][j]) > abs(am[max_row][j])) {
                max_row = i;
            }
        }
        if (abs(am[max_row][j]) < EPS) {
            continue;
        }
        if (max_row != pivot) {
            swap(am[pivot], am[max_row]);
        }
        T divisor = am[pivot][j];
        for (int k = j; k < m + 1; ++k) {
            am[pivot][k] /= divisor;
        }
        // 消去当前列 j 的其他行元素
        for (int i = 0; i < n; ++i) {
            if (i != pivot && abs(am[i][j]) > EPS) {
                T factor = am[i][j];
                for (int k = j; k < m + 1; ++k) {
                    am[i][k] -= factor * am[pivot][k];
                }
            }
        }
        pivot++;
        rank++;
    }
    for (int i = rank; i < n; ++i) {
        if (abs(am[i][m]) > EPS) {
            return {-1, {}}; // 无解
        }
    }
    if (rank == m) {
        vector<T> x(m);
        int current_row = 0;
        for (int j = 0; j < m; ++j) {
            if (current_row < n && abs(am[current_row][j]) > EPS) {
                x[j] = am[current_row][m];
                current_row++;
            } else {
                x[j] = T(0);
            }
        }
        return {1, x}; // 唯一解
    } else {
        return {0, {}}; // 无穷多解
    }
}