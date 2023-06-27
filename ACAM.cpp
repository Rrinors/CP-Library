template<int ALPHABET_SIZE = 26,
    int offset = 'a'>
struct ACAM {
    int cnt;
    std::vector<std::array<int, ALPHABET_SIZE>> _trie;
    std::vector<int> _fail;
    ACAM() : cnt(0), _trie(1), _fail(1) {}

    int newNode() {
        int sz = _trie.size();
        if (++cnt >= sz) {
            sz *= 2;
            _trie.resize(sz);
            _fail.resize(sz);
        }
        return cnt;
    }
    int insert(const std::string &s) {
        int p = 0;
        for (auto c : s) {
            if (!_trie[p][c - offset]) {
                _trie[p][c - offset] = newNode();
            }
            p = _trie[p][c - offset];
        }
        return p;
    }
    void work() {
        std::queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (_trie[u][i]) {
                    if (u) {
                        _fail[_trie[u][i]] = _trie[_fail[u]][i];
                    }
                    q.push(_trie[u][i]);
                } else {
                    _trie[u][i] = _trie[_fail[u]][i];
                }
            }
        }
    }
    int trie(int p, int c) const {
        return _trie[p][c];
    }
    int fail(int p) const {
        return _fail[p];
    }
    int size() const {
        return cnt;
    }
};