std::pair<int, std::vector<int>> SCC(auto adj) {
    int n = adj.size();
    std::vector<int> dfn(n, -1), low(n), id(n, -1), stk;
    int now = 0, tot = 0;

    auto tarjan = [&](auto self, int x) -> void {
        dfn[x] = low[x] = now++;
        stk.push_back(x);
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                self(self, y);
                low[x] = std::min(low[x], low[y]);
            } else if (id[y] == -1) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            int u;
            do {
                u = stk.back();
                stk.pop_back();
                id[u] = tot;
            } while (x != u);
            tot++;
        }
    };

    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            tarjan(tarjan, i);
        }
    }

    return {tot, id};
}