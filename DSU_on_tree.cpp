
    std::vector<int> dep(n), siz(n, 1), son(n, -1);
    auto get = [&](auto self, int x, int p) -> void {
        for (auto y : adj[x]) {
            if (y != p) {
                dep[y] = dep[x] + 1;
                self(self, y, x);
                siz[x] += siz[y];
                if (son[x] == -1 || siz[y] > siz[son[x]]) {
                    son[x] = y;
                }
            }
        }
    };

    get(get, 0, -1);

    auto modify = [&](auto self, int x, int p, int s, int v) -> void {
        // modify
        for (auto y : adj[x]) {
            if (y != p && y != s) {
                self(self, y, x, s, v);
            }
        }
    };
    
    std::vector<int> ans(n);
    auto work = [&](auto self, int x, int p, bool h) -> void {
        for (auto y : adj[x]) {
            if (y != p && y != son[x]) {
                self(self, y, x, false);
            }
        }
        if (son[x] != -1) {
            self(self, son[x], x, true);
        }
        modify(modify, x, p, son[x], 1);
        // calc ans
        if (!h) {
            modify(modify, x, p, -1, 0);
        }
    };

    work(work, 0, -1, true);
