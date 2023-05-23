template<typename T>
struct SegmentTree {
    const int n;
    std::vector<T> a;

    SegmentTree(int n) : n(n), a(4 * n) {}
    template<typename F>
    SegmentTree(const std::vector<F> &b) : SegmentTree(b.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (l == r) {
                a[p] = T(b[l]);
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 0, n - 1);
    }

    void pull(int p) {
        a[p] = a[2 * p] + a[2 * p + 1];
    }
    T rangeQuery(int p, int l, int r, int x, int y) {
        if (x > r || y < l) {
            return T();
        }
        if (x <= l && r <= y) {
            return a[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }
    T rangeQuery(int x, int y) {
        return rangeQuery(1, 0, n - 1, x, y);
    }
    void modify(int p, int l, int r, int x, const T &v) {
        if (l == r) {
            a[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x <= m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
    void modify(int x, const T &v) {
        modify(1, 0, n - 1, x, v);
    }
};