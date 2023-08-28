struct Tag {

    void apply(Tag v) {

    }
};

struct Info {

    friend Info operator+(Info a, Info b) {

    }
    void apply(Tag v) {

    }
};

template<class T, class U>
struct LazySegmentTree {
    int n;
    std::vector<T> a;
    std::vector<U> g;

    LazySegmentTree() {}
    LazySegmentTree(int n) {
        init(n);
    }
    template<class F>
    LazySegmentTree(std::vector<F> b) {
        init(b);
    }

    void init(int n) {
        this->n = n;
        a.assign(4 * n, T());
        g.assign(4 * n, U());
    }
    template<class F>
    void init(std::vector<F> b) {
        init(b.size());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (l == r) {
                a[p] = T{b[l]};
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
    void push(int p) {
        apply(2 * p, g[p]);
        apply(2 * p + 1, g[p]);
        g[p] = U();
    }
    void apply(int p, U v) {
        a[p].apply(v);
        g[p].apply(v);
    }
    void rangeApply(int p, int l, int r, int x, int y, U v) {
        if (x <= l && r <= y) {
            apply(p, v);
            return;
        }
        push(p);
        int m = (l + r) / 2;
        if (m >= x) rangeApply(2 * p, l, m, x, y, v); 
        if (m < y) rangeApply(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeApply(int x, int y, U v) {
        rangeApply(1, 0, n - 1, x, y, v);
    }
    T rangeQuery(int p, int l, int r, int x, int y) {
        if (x > r || y < l) {
            return T();
        }  
        if (x <= l && r <= y) {
            return a[p];
        }
        push(p);
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }
    T rangeQuery(int x, int y) {  
        return rangeQuery(1, 0, n - 1, x, y);
    }
    void modify(int p, int l, int r, int x, T v) {
        if (l == r) {
            a[p] = v;
            return;
        }
        push(p);
        int m = (l + r) / 2;
        if (x <= m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
    void modify(int x, T v) {
        modify(1, 0, n - 1, x, v);
    }
};