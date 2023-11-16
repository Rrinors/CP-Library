struct DonimateTree {
    int n, cur;
    std::vector<std::vector<int>> adj, radj;
    std::vector<int> dfn, order, p, semi, f, mn;

    DonimateTree(int n) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        cur = 0;
        adj.assign(n, {});
        radj.assign(n, {});
        dfn.assign(n, -1);
        order.resize(n);
        p.resize(n);
        semi.resize(n);
        f.resize(n);
        mn.resize(n);
    }
    void addEdge(int x, int y) {
        adj[x].push_back(y);
        radj[y].push_back(x);
    }
    void tarjan(int x) {
        dfn[x] = cur++;
        order[dfn[x]] = x;
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                p[y] = x;
                tarjan(y);
            }
        }
    }
    int find(int x) {
        if (x == f[x]) {
            return x;
        }
        int res = find(f[x]);
        if (dfn[semi[mn[f[x]]]] < dfn[semi[mn[x]]]) {
            mn[x] = mn[f[x]];
        }
        return f[x] = res;
    }
    std::vector<int> work(int s) {
        std::vector<int> dom(n, -1);
        std::vector<std::vector<int>> T(n);
        tarjan(s);
        for (int i = 0; i < n; i++) {
            semi[i] = f[i] = mn[i] = i;
        }
        for (int i = cur - 1; i > 0; i--) {
            int x = order[i];
            for (auto y : radj[x]) {
                if (dfn[y] == -1) {
                    continue;
                }
                find(y);
                if (dfn[semi[mn[y]]] < dfn[semi[x]]) {
                    semi[x] = semi[mn[y]];
                }
            }
            f[x] = p[x];
            T[semi[x]].push_back(x);
            x = f[x];
            for (auto y : T[x]) {
                find(y);
                dom[y] = x == semi[mn[y]] ? x : mn[y];
            }
            T[x].clear();
        }
        for (int i = 1; i < cur; i++) {
            int x = order[i];
            if (dom[x] != semi[x]) {
                dom[x] = dom[dom[x]];
            }
        }
        return dom;
    }
};