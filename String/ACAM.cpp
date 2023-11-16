template<int ALPHABET = 26>
struct ACAM {
    struct Node {
        int link;
        std::array<int, 26> ch;
        Node() : link{}, ch{} {}
    };
    std::vector<Node> t;

    ACAM() {
        init();
    }

    void init() {
        t.assign(1, Node());
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int add(std::string s, char offset = 'a') {
        int p = 0;
        for (auto c : s) {
            if (!t[p].ch[c - offset]) {
                t[p].ch[c - offset] = newNode();
            }
            p = t[p].ch[c - offset];
        }
        return p;
    }

    void work() {
        std::queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            for (int i = 0; i < ALPHABET; i++) {
                if (t[p].ch[i]) {
                    if (p) {
                        t[t[p].ch[i]].link = t[t[p].link].ch[i];
                    }
                    q.push(t[p].ch[i]);
                } else {
                    t[p].ch[i] = t[t[p].link].ch[i];
                }
            }
        }
    }

    int next(int p, int i) const {
        return t[p].ch[i];
    }

    int fail(int p) const {
        return t[p].link;
    }

    int size() const {
        return t.size();
    }

    std::vector<std::vector<int>> getTree() const {
        std::vector<std::vector<int>> adj(t.size());
        for (int i = 1; i < t.size(); i++) {
            adj[t[i].link].push_back(i);
        }
        return adj;
    }
};