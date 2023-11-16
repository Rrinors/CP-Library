template<int ALPHABET = 26>
struct SAM {
    struct Node {
        int len, link;
        std::array<int, ALPHABET> ch;
        Node() : len{}, link{-1}, ch{} {}
    } t[2 * N];

    int last, tot;

    SAM() {
        init();
    }

    void init() {
        last = 0;
        tot = 0;
        t[0] = Node();
    }

    int newNode() {
        tot++;
        t[tot] = Node();
        return tot;
    }

    int extend(int c) {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while (p != -1 && !t[p].ch[c]) {
            t[p].ch[c] = cur;
            p = t[p].link;
        }
        if (p == -1) {
            t[cur].link = 0;
        } else {
            int q = t[p].ch[c];
            if (t[p].len + 1 == t[q].len) {
                t[cur].link = q;
            } else {
                int clone = newNode();
                t[clone].len = t[p].len + 1;
                t[clone].ch = t[q].ch;
                t[clone].link = t[q].link;
                while (p != -1 && t[p].ch[c] == q) {
                    t[p].ch[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        return last = cur;
    }

    int length(int x) const {
        return t[x].len;
    }

    int fail(int x) const {
        return t[x].link;
    }

    int next(int x, int c) const {
        return t[x].ch[c];
    }

    std::vector<std::vector<int>> getTree() const {
        std::vector<std::vector<int>> adj(tot + 1);
        for (int i = 1; i <= tot; i++) {
            adj[t[i].link].push_back(i);
        }
        return adj;
    }
};