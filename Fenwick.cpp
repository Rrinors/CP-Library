template<class T>
struct Fenwick {
    int n;
    std::vector<T> a;

    Fenwick() {}
    Fenwick(int n) {
        init(n);
    }
    template<class F>
    Fenwick(std::vector<F> b) {
        init(b);
    }

    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    template<class F>
    void init(std::vector<F> b) {
        init(b.size());
        for (int i = 1; i <= n; i++) {
            a[i - 1] += T{b[i - 1]};
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