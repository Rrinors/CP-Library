
    std::vector<int> siz(n), mx(n);
    std::vector<bool> vis(n);
    int all = n, rt = -1;
    std::function<void(int, int)> get = [&](int x, int parent) {
        siz[x] = 1;
        mx[x] = 0;
        for (auto y : adj[x]) {
            if (y != parent && !vis[y]) {
                get(y, x);
                siz[x] += siz[y];
                mx[x] = std::max(mx[x], siz[y]);
            }
        }
        mx[x] = std::max(mx[x], all - siz[x]);
        if (rt == -1 || mx[rt] > mx[x]) {
            rt = x;
        }
    };

    get(0, -1);
    get(rt, -1);

    std::function<void(int, int)> calc = [&](int x, int parent) {
        // calc ans
        for (auto y : adj[x]) {
            if (y != parent && !vis[y]) {
                calc(y, x);
            }
        }
    };

    std::function<void(int, int)> modify = [&](int x, int parent) {
        // modify
        for (auto y : adj[x]) {
            if (y != parent && !vis[y]) {
                modify(y, x);
            }
        }
    };

    std::function<void(int, int)> undo = [&](int x, int parent) {
        // undo
        for (auto y : adj[x]) {
            if (y != parent && !vis[y]) {
                undo(y, x);
            }
        }
    };

    std::function<void(int)> pdc = [&](int x) {
        vis[x] = true;
        for (auto [y, w] : adj[x]) {
            if (!vis[y]) {
                calc(y, x);
                modify(y, x);
            }
        }
        undo(x, -1);
        for (auto y : adj[x]) {
            if (!vis[y]) {
                all = siz[y];
                rt = -1;
                get(y, x);
                get(rt, -1);
                pdc(rt);
            }
        }
    };

    pdc(rt);
