struct TwoSat {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<bool> ans;

    TwoSat(int n) {
        init(n);
    }
    TwoSat() {}

    void init(int n) {
        this->n = n;
        adj.assign(2 * n, {});
        ans.resize(n);
    }

    void addClause(int u, bool f, int v, bool g) {
        adj[u + f * n].push_back(v + g * n);
        adj[v + !g * n].push_back(u + !f * n);
    }

    bool work() {
        std::vector<int> dfn(2 * n, -1), low(2 * n), id(2 * n, -1);
        std::vector<int> stk;
        int cur = 0, cnt = 0;
        auto tarjan = [&](auto self, int u) -> void {
            dfn[u] = low[u] = cur++;
            stk.push_back(u);
            for (auto v : adj[u]) {
                if (dfn[v] == -1) {
                    self(self, v);
                    low[u] = std::min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (u != v);
                cnt++;
            }
        };
        for (int i = 0; i < 2 * n; i++) {
            if (dfn[i] == -1) {
                tarjan(tarjan, i);
            }
        }
        for (int i = 0; i < n; i++) {
            if (id[i] == id[i + n]) {
                return false;
            }
            ans[i] = id[i] > id[i + n];
        }
        return true;
    }
};