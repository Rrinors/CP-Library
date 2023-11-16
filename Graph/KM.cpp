struct KM {
    static constexpr i64 inf = 1E18;
    int n;
    std::vector<std::vector<i64>> a;
    std::vector<int> match, vis, pre;
    std::vector<i64> slack, lx, ly;
    KM(int n) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        a.assign(n + 1, std::vector(n + 1, -inf));
        match.assign(n + 1, -1);
        lx.assign(n + 1, 0);
        ly.assign(n + 1, 0);
    }

    void addEdge(int u, int v, i64 w) {
        a[u][v] = std::max(a[u][v], w);
    }   
    void augment(int u) {
        vis.assign(n + 1, 0);
        pre.assign(n + 1, 0);
        slack.assign(n + 1, inf);
        int x, y = 0, yy = 0;
        i64 delta;
        match[y] = u;
        while (true) {
            x = match[y];
            delta = inf;
            vis[y] = 1; 
            for (int i = 1; i <= n; ++i) {
                if (vis[i]) continue;
                if (slack[i] > lx[x] + ly[i] - a[x][i]) {
                    slack[i] = lx[x] + ly[i] - a[x][i];
                    pre[i] = y;
                }
                if (slack[i] < delta) {
                    delta = slack[i];
                    yy = i;
                }
            }
            for (int i = 0; i <= n; ++i) {
                if (vis[i]) {
                    lx[match[i]] -= delta;
                    ly[i] += delta;
                } else {
                    slack[i] -= delta;
                }
            }
            y = yy;
            if (match[y] == -1) {
                break;
            }
        }
        while (y) {
            match[y] = match[pre[y]];
            y = pre[y];
        }
    }
    i64 work() {
        for (int i = 1; i <= n; ++i) {
            augment(i);
        }
        i64 res = 0;
        for (int i = 1; i <= n; ++i) {
            if (match[i] != -1) {
                res += a[match[i]][i];
            }
        }
        return res;
    }
};