void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    auto b = a;
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());
    int sz = b.size();

    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    int B = n / (std::sqrt(m) + 1);
    B = std::max(B, 1);
    
    std::vector val(n / B + 1, std::vector<int>(n / B + 1));
    for (int i = 0; i <= n / B; i++) {
        std::vector<int> cnt(sz);
        int mode = -1;
        for (int j = i * B; j < n; j++) {
            cnt[a[j]]++;
            if (mode == -1 || cnt[a[j]] > cnt[mode]) {
                mode = a[j];
            }
            val[i][j / B] = cnt[mode];
        }
    }

    std::vector<std::vector<int>> g(sz);
    std::vector<int> order(n);
    for (int i = 0; i < n; i++) {
        order[i] = g[a[i]].size();
        g[a[i]].push_back(i);
    }

    std::vector<int> cnt(sz);
    auto query = [&](int x, int y) {
        int res = 0;
        if (y / B - x / B <= 1) {
            for (int i = x; i <= y; i++) {
                res = std::max(res, ++cnt[a[i]]);
            }
            for (int i = x; i <= y; i++) {
                cnt[a[i]]--;
            }
        } else {
            res = val[x / B + 1][y / B - 1];
            for (int i = (x / B + 1) * B - 1; i >= x; i--) {
                if (order[i] + res < g[a[i]].size() && g[a[i]][order[i] + res] <= y) {
                    res++;
                }
            }
            for (int i = y / B * B; i <= y; i++) {
                if (order[i] - res >= 0 && g[a[i]][order[i] - res] >= x) {
                    res++;
                }
            }
        }
        return res;
    };

    int lastans = 0;
    while (m--) {
        int x, y;
        std::cin >> x >> y;
        x ^= lastans, y ^= lastans;
        x--, y--;
        lastans = query(x, y);
        std::cout << lastans << "\n";
    }
}