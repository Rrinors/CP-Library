int minRotation(auto s) {
    int n = s.size();
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        if (s[(i + k) % n] == s[(j + k) % n]) {
            k++;
        } else {
            if (s[(i + k) % n] > s[(j + k) % n]) {
                i += k + 1;
            } else {
                j += k + 1;
            }
            i += i == j;
            k = 0;
        }
    }
    return std::min(i, j);
}