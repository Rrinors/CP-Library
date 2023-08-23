struct GraphMatch {
    struct Edge {
        int to, next;
        Edge(int to, int next) : to(to), next(next) {}
    };
    int tot = 0;
    std::vector<int> head, vis, f, pre, match, dfn;
    std::vector<Edge> e;
    std::queue<int> q;
    GraphMatch(int n) : head(n + 1, -1), vis(n + 1), f(n + 1),
    pre(n + 1), match(n + 1), dfn(n + 1) {}
    void addEdge(int u, int v) {
        e.emplace_back(v, head[u]);
        head[u] = int(e.size()) - 1;
        e.emplace_back(u, head[v]);
        head[v] = int(e.size()) - 1;
    }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    int lca(int x, int y) {
        ++tot;
        x = find(x);
        y = find(y);
        while (dfn[x] != tot) {
            dfn[x] = tot;
            x = find(pre[match[x]]);
            if (y) std::swap(x, y);
        }
        return x;
    }
    void shrink(int x, int y, int w) {
        while (find(x) != w) {
            pre[x] = y;
            y = match[x];
            if (vis[y] == 2) {
                vis[y] = 1;
                q.push(y);
            }
            if (find(x) == x) {
                f[x] = w;
            }
            if (find(y) == y) {
                f[y] = w;
            }
            x = pre[y];
        }
    }
    bool work(int s) {
        std::fill(vis.begin(), vis.end(), 0);
        std::fill(pre.begin(), pre.end(), 0);
        std::iota(f.begin(), f.end(), 0);
        while (!q.empty()) q.pop();
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (int i = head[u]; ~i; i = e[i].next) {
                int v = e[i].to;
                if (find(u) == find(v) || vis[v] == 2) continue;
                if (!vis[v]) {
                    vis[v] = 2;
                    pre[v] = u;
                    if (!match[v]) {
                        for (int w = v, p; w; w = p) {
                            p = match[pre[w]];
                            match[w] = pre[w];
                            match[pre[w]] = w;
                        }
                        return true;
                    }
                    vis[match[v]] = 1, q.push(match[v]);
                } else {
                    int w = lca(u, v);
                    shrink(u, v, w);
                    shrink(v, u, w);
                }
            }
        }
        return false;
    }
};