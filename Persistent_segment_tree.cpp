
constexpr int N = 200000;

int tot = 0;
int seg[21 * N], ls[21 * N], rs[21 * N];

void append(int &p, int o, int l, int r, int x) {
    p = ++tot;
    seg[p] = seg[o] + 1;
    ls[p] = ls[o];
    rs[p] = rs[o];
    if (l == r) {
        return;
    }
    int m = (l + r) / 2;
    if (x <= m) {
        append(ls[p], ls[o], l, m, x);
    } else {
        append(rs[p], rs[o], m + 1, r, x);
    }
}

int query(int x, int y, int l, int r, int k) {
    if (l == r) {
        return l;
    }
    int m = (l + r) / 2;
    int s = seg[ls[y]] - seg[ls[x]];
    if (s >= k) {
        return query(ls[x], ls[y], l, m, k);
    } else {
        return query(rs[x], rs[y], m + 1, r, k - s);
    }
}

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    auto b = a;
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());
    int sz = b.size();

    std::vector<int> tr(n + 1);
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        append(tr[i + 1], tr[i], 0, sz - 1, a[i]);
    }

    while (m--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        int ans = query(tr[l - 1], tr[r], 0, sz - 1, k); 
        std::cout << b[ans] << "\n";
    }
}