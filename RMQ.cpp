template<class T, class F>
struct RMQ {
    std::vector<std::vector<T>> a;
    F f;

    RMQ() {}
    RMQ(std::vector<T> a_, F f_) : f(f_) {
        init(a_);
    }

    void init(std::vector<T> a_) {
        int n = a_.size();
        int s = std::__lg(n);
        a.assign(s + 1, std::vector<T>(n));
        a[0] = a_;
        for (int i = 1; i <= s; i++){
            for (int j = 0; j + (1 << i) - 1 < n; j++){
                a[i][j] = f(a[i - 1][j], a[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int s = std::__lg(r - l + 1);
        return f(a[s][l], a[s][r - (1 << s) + 1]);
    }
};