
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
u64 f(u64 x) {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    u64 seed = rng();
    std::vector<u64> h(n, seed);
    std::vector<bool> sym(n);
    auto dfs = [&](auto self, int x, int parent) -> void {
        u64 sum = 0;
        for (auto y : adj[x]) {
            if (y != parent) {
                self(self, y, x);
                h[x] += f(h[y]);
                sum ^= h[y];
            }
        }

        if (sum == 0) {
            sym[x] = true;
        } else {
            for (auto y : adj[x]) {
                if (y != parent && sum == h[y] && sym[y]) {
                    sym[x] = true;
                    break;
                }
            }
        }
    };

    dfs(dfs, 0, -1);

    std::cout << (sym[0] ? "YES\n" : "NO\n");
}