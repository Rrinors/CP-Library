
constexpr int N = 2000;
void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::bitset<N>> a(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        a[x][y] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[j][i]) {
                a[j] |= a[i];
            }
        }
    }

    int ans = 0;
    for (int i = 0; auto x : a) {
        ans += x.count() - x[i];
        i++;
    }

    std::cout << ans - m << "\n";

    return 0;
}