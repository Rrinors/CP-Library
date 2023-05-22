constexpr int P = 998244353;

template<typename T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) res *= a;
    }
    return res;
}

constexpr int norm(int x) {
    return x < 0 ? x + P : x >= P ? x - P : x;
}

struct Z {
    int a;
    constexpr Z() : a{} {}
    Z(i64 a) : a(norm(a % P)) {}
    
    constexpr int val() const {
        return a;
    }
    constexpr Z inv() const {
        assert(a != 0);
        return power(*this, P - 2);
    }
    Z operator-() const {
        return norm(P - a);
    }
    constexpr Z &operator*=(const Z &rhs) {
        a = 1LL * a * rhs.a % P;
        return *this;
    }
    constexpr Z &operator+=(const Z &rhs) {
        a = norm(a + rhs.a);
        return *this;
    }
    constexpr Z &operator-=(const Z &rhs) {
        a = norm(a - rhs.a);
        return *this;
    }
    constexpr Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend constexpr Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &rhs) {
        i64 x;
        is >> x;
        rhs = Z(x);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &rhs) {
        return os << rhs.val();
    }
};

struct Comb {
    int n;
    vector<Z> _fac;
    vector<Z> _invfac;
    vector<Z> _inv;
    
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    
    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    
    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;