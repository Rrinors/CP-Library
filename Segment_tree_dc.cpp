
constexpr int N = 100010;

int n;
int edges[2 * N][2];
int f[2 * N], d[2 * N];
bool ans[N];
std::vector<int> events[4 * N];

int leader(int x) {
    while (x != f[x]) x = f[x];
    return x;
}

bool same(int x, int y) {
    return leader(x) == leader(y);
}

void modify(int p, int l, int r, int x, int y, int id) {
    if (x <= l && r <= y) {
        events[p].push_back(id);
        return;
    }
    int m = (l + r) / 2;
    if (m >= x) {
        modify(2 * p, l, m, x, y, id);
    }
    if (m < y) {
        modify(2 * p + 1, m + 1, r, x, y, id);
    }
}

void dfs(int p, int l, int r) {
    std::vector<std::pair<int, int>> stk;
    auto merge = [&](int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) {
            return;
        }
        if (d[x] < d[y]) {
            std::swap(x, y);
        }
        stk.emplace_back(y, d[x] == d[y]);
        f[y] = x;
        d[x] += d[x] == d[y];
    };
    
    bool ok = true;
    for (auto x : events[p]) {
        auto [u, v] = edges[x];
        merge(u, v + n);
        merge(u + n, v);
        if (same(u, u + n) || same(v, v + n)) {
            ok = false;
            break;
        }
    }
    
    if (ok) {
        if (l == r) {
            ans[l] = true;
        } else {
            int m = (l + r) / 2;
            dfs(2 * p, l, m);
            dfs(2 * p + 1, m + 1, r);
        }
    }
    while (!stk.empty()) {
        auto [x, y] = stk.back();
        stk.pop_back();
        d[f[x]] -= y;
        f[x] = x;
    }
}

void solve() {
    int m, k;
    std::cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> edges[i][0] >> edges[i][1] >> l >> r;
        edges[i][0]--, edges[i][1]--;
        if (l != r) {
            modify(1, 0, k, l, r - 1, i);
        }
    }

    std::iota(f, f + 2 * n, 0);
    dfs(1, 0, k);
    
    for (int i = 0; i < k; i++) {
        std::cout << (ans[i] ? "Yes\n" : "No\n");
    }
}