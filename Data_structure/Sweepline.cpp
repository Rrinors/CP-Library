
constexpr int N = 200000;

int len[4 * N], sum[4 * N], lb[4 * N], rb[4 * N];
std::vector<int> d;

void pull(int p) {
    if (sum[p]) {
        len[p] = rb[p] - lb[p];
    } else {
        len[p] = 0;
        if (2 * p < 4 * N) {
            len[p] += len[2 * p];
        }
        if (2 * p + 1 < 4 * N) {
            len[p] += len[2 * p + 1];
        }
    }
}

void modify(int p, int l, int r, int x, int y, int v) {
    lb[p] = d[l - 1];
    rb[p] = d[r];
    if (lb[p] >= x && rb[p] <= y) {
        sum[p] += v;
        pull(p);
        return;
    }
    if (lb[p] >= y || rb[p] <= x) {
        return;
    }
    int m = (l + r) / 2;
    modify(2 * p, l, m, x, y, v);
    modify(2 * p + 1, m + 1, r, x, y, v);
    pull(p);
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<array<int, 4>> edges;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        d.push_back(x1);
        d.push_back(x2);
        edges.push_back({x1, x2, y1, 1});
        edges.push_back({x1, x2, y2, -1});
    }

    std::sort(d.begin(), d.end());
    d.erase(std::unique(d.begin(), d.end()), d.end());
    int sz = int(d.size()) - 1;

    std::sort(edges.begin(), edges.end(), [&](auto x, auto y) {
        return x[2] < y[2];
    });

    i64 ans = 0;
    int py = -1;
    for (auto [x1, x2, y, v] : edges) {
        if (py != -1) {
            ans += 1LL * (y - py) * len[1];
        }
        modify(1, 1, sz, x1, x2, v);
        py = y;
    }

    std::cout << ans << "\n";
}