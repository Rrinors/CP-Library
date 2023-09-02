template<class T, int N>
struct SeqLinearBasis {
    std::array<T, N> p;
    std::array<int, N> t;
    SeqLinearBasis() : p{} {
        t.fill(-1);
    }

    bool add(T x, int cur) {
        for (int i = N - 1; i >= 0; i--) {
            if (!(x >> i)) {
                continue;
            }
            if (!p[i]) {
                p[i] = x;
                t[i] = cur;
                return true;
            }
            if (cur > t[i]) {
                std::swap(x, p[i]);
                std::swap(cur, t[i]);
            }
            x ^= p[i];
        }
        return false;
    }
    T max(int l) {
        T res = 0;
        for (int i = N - 1; i >= 0; i--) {
            if (t[i] >= l) {
                res = std::max(res, res ^ p[i]);
            }
        }
        return res;
    }
};

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }

    std::vector<SeqLinearBasis<int, 20>> h(n);
    for (int i = 0; i < n; i++) {
        if (i) {
            h[i] = h[i - 1];
        }
        h[i].add(c[i], i);
    }

    int q;
    std::cin >> q;

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--, r--;
        std::cout << h[r].max(l) << "\n";
    }
}