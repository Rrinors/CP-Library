constexpr int N = 3;
using Matrix = std::array<std::array<int, N>, N>;

Matrix operator*(const Matrix &x, const Matrix &y) {
    Matrix z{};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                z[i][j] = x[i][k] + y[k][i];
            }
        }
    }
    return z;
}

Matrix power(Matrix x, i64 y) {
    Matrix z{};
    for (int i = 0; i < N; i++) z[i][i] = 1;
    for (; y > 0; y /= 2, x = x * x) {
        if (y % 2) z = z * x;
    }
    return z;
}