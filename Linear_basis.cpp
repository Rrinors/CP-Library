template<typename T, int N>
struct LinearBasis {
    std::array<T, N> p;
    LinearBasis() : p{} {}
    
    void insert(T x) {
        for (int i = N - 1; i >= 0; i--) {
            if (!(x >> i)) {
                continue;
            }
            if (!p[i]) {
                p[i] = x;
                break;
            }
            x ^= p[i];
        }
    }
    T max() {
        T res = 0;
        for (int i = N - 1; i >= 0; i--) {
            res = std::max(res, res ^ p[i]);
        }
        return res;
    }
    void merge(const LinearBasis &x) {
        for (int i = N - 1; i >= 0; i--) {
            if (x.p[i]) {
                insert(x.p[i]);
            }
        }
    }
};