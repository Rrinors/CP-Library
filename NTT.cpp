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

std::vector<Z> roots{0, 1};
std::vector<int> rev;
using Poly = std::vector<Z>;
void dft(Poly &a) {
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
    for (int i = 0; i < n; i++) {
        if (rev[i] < i) {
            std::swap(a[i], a[rev[i]]);
        }
    }
    if (int(roots.size()) < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            Z e = power(Z(3), (P - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * e;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                Z u = a[i + j];
                Z v = a[i + j + k] * roots[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}
void idft(Poly &a) {
    int n = a.size();
    reverse(a.begin() + 1, a.end());
    dft(a);
    Z inv = (1 - P) / n;
    for (int i = 0; i < n; i++) {
        a[i] *= inv;
    }
}
Poly convolution(Poly a, Poly b) {
    if (a.size() == 0 || b.size() == 0) {
        return Poly();
    }
    int sz = 1, tot = a.size() + b.size() - 1;
    while (sz < tot) {
        sz *= 2;
    }
    a.resize(sz);
    b.resize(sz);
    dft(a);
    dft(b);
    for (int i = 0; i < sz; ++i) {
        a[i] = a[i] * b[i];
    }
    idft(a);
    a.resize(tot);
    return a;
}