
void solve_3() {
    int n, m;
    cin >> n >> m;

    vector<array<int, 2>> edges(m);
    vector<int> d(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        d[u]++;
        d[v]++;
        edges[i] = {u, v};
    }

    vector<vector<int>> adj(n);
    for (auto [x, y] : edges) {
        if (d[x] > d[y] || d[x] == d[y] && x < y) {
            adj[x].push_back(y);
        } else {
            adj[y].push_back(x);
        }
    }

    int ans = 0;
    vector<int> col(n, -1);

    for (int i = 0; i < n; i++) {
        for (auto j : adj[i]) {
            col[j] = i;
        }
        for (auto j : adj[i]) {
            for (auto k : adj[j]) {
                if (col[k] == i) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}

void solve_4() {
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