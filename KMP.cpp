std::vector<int> kmp(const std::string &s) {
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