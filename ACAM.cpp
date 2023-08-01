template<int ALPHABET_SIZE = 26,
    char offset = 'a'>
struct ACAM {
    std::vector<std::array<int, ALPHABET_SIZE>> t;
    std::vector<int> f;
    ACAM() { init(); }

    void init() {
        t.assign(1, {});
        f.assign(1, 0);
    }
    int newNode() {
        t.emplace_back();
        f.emplace_back();
        return t.size() - 1;
    }
    int insert(const std::string &s) {
        int p = 0;
        for (auto c : s) {
            if (!t[p][c - offset]) {
                t[p][c - offset] = newNode();
            }
            p = t[p][c - offset];
        }
        return p;
    }
    void work() {
        std::queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (t[p][i]) {
                    if (p) {
                        f[t[p][i]] = t[f[p]][i];
                    }
                    q.push(t[p][i]);
                } else {
                    t[p][i] = t[f[p]][i];
                }
            }
        }
    }

    int next(int p, int i) {
        return t[p][i];
    }
    int fail(int p) {
        return f[p];
    }
    int size() {
        return t.size();
    }
    std::vector<std::vector<int>> failTree() {
        std::vector<std::vector<int>> adj(t.size());
        for (int i = 1; i < t.size(); i++) {
            adj[fail(i)].push_back(i);
        }
        return adj;
    }
};