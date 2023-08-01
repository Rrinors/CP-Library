template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
 
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
};
 
template<>
int MInt<0>::Mod = 1;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

template<int P1, int P2>
struct MPair {
    MInt<P1> x;
    MInt<P2> y;
    constexpr MPair() : x{}, y{} {}
    constexpr MPair(i64 x_, i64 y_) : x(x_), y(y_) {}
    constexpr MPair(i64 x_) : x(x_), y(x_) {}
 
    constexpr MPair &operator+=(MPair rhs) & {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    constexpr MPair &operator-=(MPair rhs) & {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    constexpr MPair &operator*=(MPair rhs) & {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }
    constexpr MPair &operator/=(MPair rhs) & {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }
    friend constexpr MPair operator+(MPair lhs, MPair rhs) {
        MPair res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MPair operator-(MPair lhs, MPair rhs) {
        MPair res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MPair operator*(MPair lhs, MPair rhs) {
        MPair res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MPair operator/(MPair lhs, MPair rhs) {
        MPair res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr bool operator==(MPair lhs, MPair rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend constexpr bool operator<(MPair lhs, MPair rhs) {
        return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
    }
};

constexpr int P1 = 1000000829;
constexpr int P2 = 1000000579;
using Hash = MPair<P1, P2>;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());