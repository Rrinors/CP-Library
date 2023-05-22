
constexpr int N = 100005;

struct Info {
    double maxk;
    int ans;
    Info(double maxk = 0, int ans = 0) : maxk(maxk), ans(ans) {}
} seg[4 * N];

int get(int p, int l, int r, double mx) {
    if (l == r) {
        return seg[p].maxk > mx;
    }
    int m = (l + r) / 2;
    if (seg[2 * p].maxk <= mx) {
        return get(2 * p + 1, m + 1, r, mx);
    } else {
        return get(2 * p, l, m, mx) + seg[p].ans - seg[2 * p].ans;
    }
}

void pull(int p, int l, int r) {
    seg[p].maxk = std::max(seg[2 * p].maxk, seg[2 * p + 1].maxk);
    seg[p].ans = seg[2 * p].ans + get(2 * p + 1, (l + r) / 2 + 1, r, seg[2 * p].maxk);
}

void modify(int p, int l, int r, int x, int y) {
    if (l == r) {
        seg[p].maxk = 1. * y / x;
        seg[p].ans = (y > 0);
        return;
    }

    int m = (l + r) / 2;
    if (x <= m) {
        modify(2 * p, l, m, x, y);
    } else {
        modify(2 * p + 1, m + 1, r, x, y);
    }
    pull(p, l, r);
}

void solve() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        modify(1, 1, n, x, y);
        std::cout << seg[1].ans << "\n";
    }
}