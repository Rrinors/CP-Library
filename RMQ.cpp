template<class T, auto f>
struct RMQ {
    std::vector<std::vector<T>> a;
    RMQ(const std::vector<T> &b) {
        init(b);
    }
    RMQ() {}

    void init(const std::vector<T> &b) {
        int n = b.size();
        int s = 31 - __builtin_clz(n);
        a.assign(s + 1, std::vector<T>(n));
        a[0] = b;
        for (int i = 1; i <= s; i++){
            for (int j = 0; j + (1 << i) - 1 < n; j++){
                a[i][j] = f(a[i - 1][j], a[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T query(int l, int r) {
        assert(l <= r);
        int s = 31 - __builtin_clz(r - l + 1);
        return f(a[s][l], a[s][r - (1 << s) + 1]);
    }
};