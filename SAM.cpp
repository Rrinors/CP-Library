template<int ALPHABET_SIZE = 26>
struct SAM {
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{-1}, next{} {}
    };
    int last;
    std::vector<Node> t;
    SAM() { init(); }

    void init() {
        last = 0;
        t.assign(1, Node());
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int c) {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while (p != -1 && !t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        if (p == -1) {
            t[p].link = 0;
        } else {
            int q = t[p].next[c];
            if (t[p].len + 1 == t[q].len) {
                t[cur].link = q;
            } else {
                int clone = newNode();
                t[clone].len = t[p].len + 1;
                t[clone].next = t[q].next;
                t[clone].link = t[q].link;
                while (p != -1 && t[p].next[c] == q) {
                    t[p].next[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        return last = cur;
    }
    
    int len(int x) {
        return t[x].len;
    }
    int link(int x) {
        return t[x].link;
    }
    int next(int x, int c) {
        return t[x].next[c];
    }
    int size() {
        return t.size();
    }
    std::vector<std::vector<int>> parentTree() {
        std::vector<std::vector<int>> adj(t.size());
        for (int i = 1; i < t.size(); i++) {
            adj[link(i)].push_back(i);
        }   
        return adj;
    }
};