template<int P1, int P2>
struct MPair {
    MInt<P1> x;
    MInt<P2> y;
    constexpr MPair() : x{}, y{} {}
    constexpr MPair(i64 _x, i64 _y) : x(_x), y(_y) {}
    constexpr MPair(i64 _x) : x(_x), y(_x) {}
 
    constexpr MPair &operator+=(const MPair &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    constexpr MPair &operator-=(const MPair &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    constexpr MPair &operator*=(const MPair &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }
    friend constexpr MPair operator+(const MPair &lhs, const MPair &rhs) {
        MPair res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MPair operator-(const MPair &lhs, const MPair &rhs) {
        MPair res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MPair operator*(const MPair &lhs, const MPair &rhs) {
        MPair res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr bool operator==(const MPair &lhs, const MPair &rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend constexpr bool operator<(const MPair &lhs, const MPair &rhs) {
        return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
    }
};

constexpr int P1 = 1000000829;
constexpr int P2 = 1000000579;
using Z = MPair<P1, P2>;