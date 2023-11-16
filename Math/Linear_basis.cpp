template<class T, int N>
struct LinearBasis {
    std::array<T, N> p;
    LinearBasis() : p{} {}
    
    bool add(T x) {
        for (int i = N - 1; i >= 0; i--) {
            if (!(x >> i)) {
                continue;
            }
            if (!p[i]) {
                p[i] = x;
                return true;
            }
            x ^= p[i];
        }
        return false;
    }
    T max() {
        T res = 0;
        for (int i = N - 1; i >= 0; i--) {
            res = std::max(res, res ^ p[i]);
        }
        return res;
    }
    LinearBasis &operator+=(LinearBasis b) & {
        for (int i = N - 1; i >= 0; i--) {
            if (b.p[i]) {
                add(b.p[i]);
            }
        }
    }
};