
    std::vector<int> parent(n), dep(n), siz(n);
    auto dfs1 = [&](auto self, int u) -> void {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            self(self, v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    };

    parent[0] = -1;
    dfs1(dfs1, 0);

    std::vector<int> top(n), dfn(n), seq(n);
    int cur = 0;
    auto dfs2 = [&](auto self, int u) -> void {
        dfn[u] = cur++;
        seq[dfn[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            self(self, v);
        }
    };

    top[0] = 0;
    dfs2(dfs2, 0);

    auto lca = [&](int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    };

    auto dist = [&](int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    };

    auto jump = [&](int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }   
        return seq[dfn[u] - dep[u] + d];
    };

    auto isAncester = [&](int u, int v) {
        return dfn[v] >= dfn[u] && dfn[v] < dfn[u] + siz[u];
    };

    auto rootedParent = [&](int u, int v) {
        if (u == v) {
            return u;
        }
        if (!isAncester(v, u)) {
            return parent[v];
        }
        auto it = std::upper_bound(adj[v].begin(), adj[v].end(), u, [&](int x, int y) {
            return dfn[x] < dfn[y];
        }) - 1;
        return *it;
    };

    auto rootedSize = [&](int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    };

    auto rootedLca = [&](int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    };