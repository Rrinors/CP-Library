template<typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    template<typename F>
    Fenwick(const std::vector<F> &b) : Fenwick(b.size()) {
        for (int i = 1; i <= n; i++) {
            a[i - 1] += b[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                a[j - 1] += a[i - 1];
            }
        }
    }

    void add(int x, T v) { 
        for(int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v; 
        }
    }
    T sum(int x) {
        T res = T();
        for(int i = x + 1; i > 0; i -= i & -i) {
            res += a[i - 1];      
        }
        return res;
    }
    T rangeSum(int l, int r) {
        if (l > r) {
            return T();
        }
        return sum(r) - sum(l - 1); 
    }
};