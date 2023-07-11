std::pair<std::vector<int>, std::vector<int>> suffixArray(std::string &s) {
    int n = s.length();
    int m = 128;
    std::vector<int> sa(n), rk(n), cnt(std::max(m, n));

    for (int i = 0; i < m; i++) {
        cnt[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        cnt[rk[i] = s[i]]++;
    }

    for (int i = 1; i < m; i++) {
        cnt[i] += cnt[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        sa[--cnt[rk[i]]] = i;
    }

    int p;
    std::vector<int> id(n), key(n);
    auto cmp = [&](int x, int y, int w) {
        if (id[x] != id[y]) {
            return false;
        }
        x = x + w < n ? id[x + w] : -1;
        y = y + w < n ? id[y + w] : -1;
        return x == y;
    };

    for (int w = 1; p < n; w *= 2, m = p) {
        p = 0;
        for (int i = n - w; i < n; i++) {
            id[p++] = i;
        }
        for (int i = 0; i < n; i++) {
            if (sa[i] >= w) {
                id[p++] = sa[i] - w;
            }
        }
        cnt.assign(m, 0);
        for (int i = 0; i < n; i++) {
            cnt[key[i] = rk[id[i]]]++;
        }
        for (int i = 1; i < m; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            sa[--cnt[key[i]]] = id[i];
        }
        std::swap(rk, id);
        rk[sa[0]] = 0;
        p = 1;
        for (int i = 1; i < n; i++) {
            rk[sa[i]] = cmp(sa[i - 1], sa[i], w) ? p - 1: p++;
        }
    }

    return {sa, rk};
}

void solve() {
    std::string s;
    std::cin >> s;
    int n = s.length();

    auto [sa, rk] = suffixArray(s);
    std::vector<int> height(n);
    for (int i = 0, k = 0; i < n; i++) {
        if (rk[i] == 0) {
            continue;
        }
        if (k) {
            k--;
        }
        while (i + k < n && sa[rk[i] - 1] + k < n && s[i + k] == s[sa[rk[i] - 1] + k]) {
            k++;
        }
        height[rk[i]] = k;
    }

    
}