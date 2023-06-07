#include <bits/stdc++.h>

using i64 = long long;

constexpr int P = 1000000007;

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
    explicit constexpr operator int() const {
        return a;
    }
};

struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;
    
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

std::vector<int> minp, primes;
std::vector<Z> pw;
void sieve(int n, int k) {
    minp.assign(n + 1, 0);
    pw.assign(n + 1, 0);
    primes.clear();
    pw[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
            pw[i] = power(Z(i), k);
        }
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            pw[i * p] = pw[i] * pw[p];
            if (p == minp[i]) {
                break;
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;

    sieve(k + 2, k);

    std::vector<Z> val(k + 3);
    for (int i = 1; i <= k + 2; i++) {
        val[i] = val[i - 1] + pw[i];
    }

    std::vector<Z> pre(k + 3), suf(k + 4);
    pre[0] = 1;
    for (int i = 1; i <= k + 2; i++) {
        pre[i] = pre[i - 1] * (n - i);
    }
    suf[k + 3] = 1;
    for (int i = k + 2; i; i--) {
        suf[i] = suf[i + 1] * (n - i);
    }

    Z ans = 0;
    for (int i = 1; i <= k + 2; i++) {
        int o = (k + 2 - i) % 2 ? -1 : 1;
        ans += val[i] * pre[i - 1] * suf[i + 1] * comb.invfac(i - 1) * comb.invfac(k + 2 - i) * o;
    }

    std::cout << ans << "\n";
    
    return 0;
}