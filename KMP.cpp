std::vector<int> kmp(std::string s) {
    int n = s.length();
    std::vector<int> next(n + 1);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) {
            j = next[j];
        }
        j += s[i] == s[j];
        next[i + 1] = j;
    }
    return next;
}

std::vector<int> zFunction(std::string s) {
    int n = s.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        } else {
            z[i] = std::max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}