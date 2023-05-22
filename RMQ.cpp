template<typename T>
struct RMQ {
    const int n;
    std::vector<std::vector<T>> a;
    std::function<T(T, T)> f;
    RMQ(const std::vector<T> &b, std::function<T(T, T)> f) : n(b.size()),
    f(f), a(32 - __builtin_clz(n), std::vector<T>(n)) {
        int s = 31 - __builtin_clz(n);
        a[0] = b;
        for (int i = 1; i <= s; i++){
            for (int j = 0; j + (1 << i) - 1 < n; j++){
                a[i][j] = f(a[i - 1][j], a[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T query(int l, int r) {
        int s = 31 - __builtin_clz(r - l + 1);
        return f(a[s][l], a[s][r - (1 << s) + 1]);
    }
};