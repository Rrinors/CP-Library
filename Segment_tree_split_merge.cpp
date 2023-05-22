
constexpr int N = 200000;

int cntNodes = 0;
i64 seg[60 * N];
int ls[60 * N], rs[60 * N];

void pull(int p) {
    seg[p] = seg[ls[p]] + seg[rs[p]];
}

void modify(int &p, int l, int r, int x, int v) {
    if (!p) {
        p = ++cntNodes;
    }
    if (l == r) {
        seg[p] += v;
        return;
    }
    int m = (l + r) / 2;
    if (x <= m) {
        modify(ls[p], l, m, x, v);
    } else {
        modify(rs[p], m + 1, r, x, v);
    }
    pull(p);
}

i64 rangeQuery(int p, int l, int r, int x, int y) {
    if (r < x || l > y) {
        return 0;
    }
    if (x <= l && r <= y) {
        return seg[p];
    }
    int m = (l + r) / 2;
    return rangeQuery(ls[p], l, m, x, y) + rangeQuery(rs[p], m + 1, r, x, y);
}

int kth(int p, int l, int r, i64 k) {
    if (seg[p] < k) {
        return -1;
    }
    if (l == r) {
        return l;
    }
    int m = (l + r) / 2;
    int t = kth(ls[p], l, m, k);
    return t == -1 ? kth(rs[p], m + 1, r, k - seg[ls[p]]) : t;
}

int merge(int x, int y) {
    if (!x || !y) {
        return x + y;
    }
    seg[x] += seg[y];
    ls[x] = merge(ls[x], ls[y]);
    rs[x] = merge(rs[x], rs[y]);
    return x;
}

void split(int x, int &y, i64 k) {
    if (x == 0) {
        return;
    }
    y = ++cntNodes;
    i64 v = seg[ls[x]];
    if (k > v) {
        split(rs[x], rs[y], k - v);
    } else {
        std::swap(rs[x], rs[y]);
    }
    if (k < v) {
        split(ls[x], ls[y], k);
    }
    seg[y] = seg[x] - k;
    seg[x] = k;
}
