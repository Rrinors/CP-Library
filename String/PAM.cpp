template<int ALPHABET = 26>
struct PAM {
    struct Node {
        int len, link;
        std::array<int, ALPHABET> ch;
        Node() : len{}, link{}, ch{} {}
    } t[N + 2];
    
    int p, tot, cur;
    int s[N];

    PAM() {
        init();
    }

    void init() {
        p = 0;
        tot = 1;
        cur = 0;
        t[0] = {0, 1};
        t[1] = {-1};
    }

    int newNode() {
        tot++;
        t[tot] = Node();
        return tot;
    }

    int get(int p, int i) const {
        while (i - t[p].len - 1 < 0 || s[i] != s[i - t[p].len - 1]) {
            p = t[p].link;
        }
        return p;
    }

    int extend(int c) {
        s[cur] = c;
        p = get(p, cur);
        if (!t[p].ch[c]) {
            int r = newNode();
            t[r].link = t[get(t[p].link, cur)].ch[c];
            t[p].ch[c] = r;
            t[r].len = t[p].len + 2;
        }
        p = t[p].ch[c];
        cur++;
        return p;
    }

    int length(int p) const {
        return t[p].len;
    }

    int fail(int p) const {
        return t[p].link;
    }

    int next(int p, int c) const {
        return t[p].ch[c];
    }

    std::vector<std::vector<int>> getTree() const {
        std::vector<std::vector<int>> adj(tot + 1);
        for (int i = 0; i <= tot; i++) {
            if (i != 1) {
                adj[fail(i)].push_back(i);
            }
        }
        return adj;
    };
};