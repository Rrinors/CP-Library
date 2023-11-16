std::vector<std::vector<int>> PBCC(auto &adj) {
    int n = adj.size();
    std::vector<std::vector<int>> T(2 * n);
    std::vector<int> dfn(n, -1), low(n), stk;
    int now = 0, tot = n;

    std::function<void(int)> tarjan = [&](int x) {
        dfn[x] = low[x] = now++;
        stk.push_back(x);
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                tarjan(y);
                low[x] = std::min(low[x], low[y]);
                if (low[y] == dfn[x]) {
                    int t;
                    do {
                        t = stk.back();
                        stk.pop_back();
                        T[t].push_back(tot);
                        T[tot].push_back(t);
                    } while (t != x && t != y);
                    T[x].push_back(tot);
                    T[tot].push_back(x);
                    tot++;
                }
            } else {
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            tarjan(i);
            stk.pop_back();
        }
    }
    
    T.resize(tot);
    return T;
}
