struct BitSet {
    using u64 = unsigned long long;
    int n;
    std::vector<u64> a;

    BitSet() {}
    BitSet(int n) {
        init(n);
    }
    BitSet(std::string s) {
        init(s);
    }

    void init(int n) {
        this->n = n;
        a.assign((n + 63) / 64, 0);
    }
    void init(std::string s) {
        init(s.length());
        for (int i = 0; i < n; i++) {
            set(n - i - 1, s[i] - '0');
        }
    }
    void norm() {
        if (n == 0) {
            return;
        }
        int shift = 63 - (n - 1) % 64;
        a.back() = a.back() << shift >> shift;
    }

    int operator[](int x) const {
        if (x < 0 || x >= n) {
            return 0;
        }
        int id = x / 64;
        return a[id] >> (x - id * 64) & 1;
    }
    void set(int x, int v) {
        if (x < 0 || x >= n) {
            return;
        }
        int id = x / 64;
        if ((a[id] >> (x - id * 64) & 1) != v) {
            a[id] ^= 1ULL << (x - id * 64);
        }
    }
    BitSet &operator&=(BitSet rhs) & {
        int m = std::min(a.size(), rhs.a.size());
        for (int i = 0; i < m; i++) {
            a[i] &= rhs.a[i];
        }
        norm();
        return *this;
    }
    BitSet &operator|=(BitSet rhs) & {
        int m = std::min(a.size(), rhs.a.size());
        for (int i = 0; i < m; i++) {
            a[i] |= rhs.a[i];
        }
        norm();
        return *this;
    }
    BitSet &operator^=(BitSet rhs) & {
        int m = std::min(a.size(), rhs.a.size());
        for (int i = 0; i < m; i++) {
            a[i] ^= rhs.a[i];
        }
        norm();
        return *this;
    }
    BitSet &operator<<=(int k) & {
        int m = a.size();
        for (int i = m - 1; i >= 0; i--) {
            int l = i * 64 - k;
            int r = l + 63;
            if (r < 0) {
                a[i] = 0;
            } else if (l % 64 == 0) {
                a[i] = a[l / 64];
            } else {
                int shift = r % 64;
                u64 v = 0;
                if (l > 0) {
                    v += a[l / 64] >> (shift + 1);
                }
                v += a[r / 64] << (63 - shift);
                a[i] = v;
            }
        }
        norm();
        return *this;
    }
    BitSet &operator>>=(int k) & {
        int m = a.size();
        for (int i = 0; i < m; i++) {
            int l = i * 64 + k;
            int r = l + 63;
            if (l >= m * 64) {
                a[i] = 0;
            } else if (l % 64 == 0) {
                a[i] = a[l / 64];
            } else {
                int shift = r % 64;
                u64 v = 0;
                v += a[l / 64] >> (shift + 1);
                if (r / 64 < m) {
                    v += a[r / 64] << (63 - shift);
                }
                a[i] = v;
            }
        }
        norm();
        return *this;
    }
    friend BitSet operator&(BitSet lhs, BitSet rhs) {
        return lhs &= rhs;
    }
    friend BitSet operator|(BitSet lhs, BitSet rhs) {
        return lhs |= rhs;
    }
    friend BitSet operator^(BitSet lhs, BitSet rhs) {
        return lhs ^= rhs;
    }
    friend BitSet operator<<(BitSet lhs, int k) {
        return lhs <<= k;
    }
    friend BitSet operator>>(BitSet lhs, int k) {
        return lhs >>= k;
    }
    friend bool operator==(BitSet lhs, BitSet rhs) {
        if (lhs.n != rhs.n) {
            return false;
        }
        int m = lhs.a.size();
        for (int i = 0; i < m; i++) {
            if (lhs.a[i] != rhs.a[i]) {
                return false;
            }
        }
        return true;
    }
    friend bool operator<(BitSet lhs, BitSet rhs) {
        assert(lhs.a.size() == rhs.a.size());
        int m = lhs.a.size();
        for (int i = 0; i < m; i++) {
            if (lhs.a[i] < rhs.a[i]) {
                return true;
            }
            if (lhs.a[i] > rhs.a[i]) {
                return false;
            }
        }
        return false;
    }
    int findFirst() const {
        int m = a.size();
        for (int i = 0; i < m; i++) {
            if (a[i] != 0) {
                for (int j = 0; j < 64; j++) {
                    if (a[i] >> j & 1) {
                        return i * 64 + j;
                    }
                }
            }
        }
        return n;
    }
    int findLast() const {
        int m = a.size();
        for (int i = m - 1; i >= 0; i--) {
            if (a[i] != 0) {
                for (int j = 63; j >= 0; j--) {
                    if (a[i] >> j & 1) {
                        return i * 64 + j;
                    }
                }
            }
        }
        return -1;
    }
    int count() const {
        int ans = 0;
        for (auto x : a) {
            ans += __builtin_popcountll(x);
        }
        return ans;
    }
    friend std::ostream &operator<<(std::ostream &os, BitSet b) {
        for (int i = b.n - 1; i >= 0; i--) {
            os << b[i];
        }
        return os;
    }
};