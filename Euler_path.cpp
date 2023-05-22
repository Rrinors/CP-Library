void solve_dg() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> in(n), out(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        out[u]++;
        in[v]++;
    }

    int st = 0, cnt1 = 0, cnt2 = 0;
    bool nice = true;
    for (int i = 0; i < n; i++) {
        // std::sort(adj[i].begin(), adj[i].end());
        if (std::abs(in[i] - out[i]) > 1) {
            nice = false;
            break;
        }
        if (out[i] > in[i]) {
            cnt1++;
            st = i;
        } else if (out[i] < in[i]) {
            cnt2++;
        }
    }

    if (cnt1 > 1 || cnt2 > 1) {
        nice = false;
    }

    if (!nice) {
        std::cout << "No\n";
        return;
    }

    std::vector<int> stk, cur(n);
    auto dfs = [&](auto self, int x) -> void {
        for (int &i = cur[x]; i < adj[x].size(); ) {
            int y = adj[x][i++];
            self(self, y);
        }
        stk.push_back(x);
    };

    dfs(dfs, st);
    std::reverse(stk.begin(), stk.end());

    for (auto x : stk) {
        std::cout << x + 1 << "\n";
    }
}

void solve_ug() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    std::vector<int> e;
    auto add = [&](int u, int v) {
        g[u].push_back(e.size());
        e.push_back(v);
        g[v].push_back(e.size());
        e.push_back(u);
    };

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        add(u, v);
    }

    int st = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (g[i].size() % 2) {
            cnt++;
            st = i;
        }
    }

    if (cnt > 2) {
        std::cout << "NO\n";
    }

    std::vector<bool> vis(e.size());
    std::vector<int> stk, cur(n);
    auto dfs = [&](auto self, int x) -> void {
        for (int &i = cur[x]; i < g[x].size(); ++i) {
            int j = g[x][i];
            int v = e[j];
            if (!vis[j]) {
                vis[j] = vis[j ^ 1] = true;
                self(self, v);
            }
        }
        stk.push_back(x);
    };

    dfs(dfs, st);
    std::reverse(stk.begin(), stk.end());

    for (auto x : stk) {
        std::cout << x + 1 << "\n";
    }
}