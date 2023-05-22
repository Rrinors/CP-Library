std::pair<int, std::vector<int>> EBCC(auto &adj) {
    int n = adj.size();
    std::vector<int> dfn(n, -1), low(n), id(n), stk;
    std::vector<bool> vis;
    int now = 0, cnt = 0;
    
    auto check = [&](int x) {
        if (x >= vis.size()) {
            vis.resize(x + 1);
        }
        return vis[x];
    };

    auto tarjan = [&](auto self, int x) -> void {
        dfn[x] = low[x] = now++;
        stk.push_back(x);
        for (auto [y, i] : adj[x]) {
            if (check(i)) {
                continue;
            }
            vis[i] = true;
            if (dfn[y] == -1) {
                self(self, y);
                low[x] = std::min(low[x], low[y]);
            } else {
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                stk.pop_back();
                id[y] = cnt;
            } while (x != y);
            cnt++;
        }
    };

    tarjan(tarjan, 0);
    return {cnt, id};
}