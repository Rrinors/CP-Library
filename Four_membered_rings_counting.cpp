void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<pair<int, int>> e(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        e[i] = {u, v};
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) {
        return adj[i].size() == adj[j].size() ? i < j : adj[i].size() < adj[j].size();
    });

    vector<int> rk(n);
    for (int i = 0; i < n; i++) {
        rk[p[i]] = i;
    }

    vector<vector<int>> g(n);
    for (auto [x, y] : e) {
        if (rk[y] > rk[x]) {
            g[x].push_back(y);
        } else {
            g[y].push_back(x);
        }
    }

    int ans = 0;
    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        for (auto j : adj[i]) {
            for (auto k : g[j]) {
                if (rk[k] > rk[i]) {
                    ans += cnt[k]++;
                }
            }
        }
        for (auto j : adj[i]) {
            for (auto k : g[j]) {
                if (rk[k] > rk[i]) {
                    cnt[k] = 0;
                }
            }
        }
    }

    cout << ans << "\n";
}