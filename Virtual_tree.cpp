    std::vector<std::vector<int>> T(n);
    auto build = [&](std::vector<int> &v) {
        v.push_back(0);
        std::sort(v.begin(), v.end(), [&](int i, int j) {
            return dfn[i] < dfn[j];
        });
        for (int i = 0, len = v.size(); i < len - 1; i++) {
            v.push_back(lca(v[i], v[i + 1]));
        }
        std::sort(v.begin(), v.end(), [&](int i, int j) {
            return dfn[i] < dfn[j];
        });
        v.erase(std::unique(v.begin(), v.end()), v.end());
        std::vector<int> stk {0};
        for (auto x : v) {
            if (!x) {
                continue;
            }
            while (dfn[x] >= dfn[stk.back()] + siz[stk.back()]) {
                stk.pop_back();
            }
            T[stk.back()].push_back(x);
            stk.push_back(x);
        }
    };

    auto dfs = [&](auto self, int x, int parent) -> void {
        // work
        for (auto y : T[x]) {
            self(self, y, x);
        }
    };

    for (now = 0; now < n; now++) {
        build(g[now]);
        dfs(dfs, 0, -1);
        // calc ans
        for (auto x : g[now]) {
            T[x].clear();
        }
    }
