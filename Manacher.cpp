std::vector<int> manacher(std::string &s) {
    int n = s.length();
    std::string t(2 * n + 1, '#');
    for (int i = 0; i < n; i++) {
        t[2 * i + 1] = s[i];
    }
    n = 2 * n + 1;
    std::vector<int> p(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        p[i] = r > i ? std::min(p[l + r - i], r - i) : 1;
        while (i + p[i] < n && i - p[i] >= 0 && t[i + p[i]] == t[i - p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            r = i + p[i];
            l = i - p[i];
        }
    }
    return p;
}