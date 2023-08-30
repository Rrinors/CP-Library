
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
using Z = MPair<P1, P2>;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());