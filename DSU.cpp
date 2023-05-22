struct DSU {
    int cnt;
    std::vector<int> f, siz;
    DSU(int n) : cnt(n), f(n), siz(n, 1) {
        std::iota(f.begin(), f.end(), 0);
    }
    
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return false;
        cnt--;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    bool same(int x, int y) {
        return leader(x) == leader(y);
    }
    int size(int x) {
        return siz[leader(x)];
    }
    int comps() const {
        return cnt;
    }
};