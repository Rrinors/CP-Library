template<typename T>
constexpr T eps;

template<>
constexpr int eps<int> = 0;

template<>
constexpr i64 eps<i64> = 0;

template<>
constexpr double eps<double> = 1E-6;

template<>
constexpr long double eps<long double> = 1E-8;

template<typename T>
constexpr int sgn(T x) {
    if (x > eps<T>) {
        return 1;
    }
    if (x < eps<T>) {
        return -1;
    }
    return 0;
}

// Point
template<typename T>
struct Point {
    T x;
    T y;

    constexpr Point() : x{}, y{} {}
    constexpr Point(T _x, T _y) : x(_x), y(_y) {}
    template<typename F>
    constexpr Point(const Point<F> &a) : x(a.x), y(a.y) {}
    
    constexpr Point operator-() const {
        return {-x, -y};
    }
    template<class F>
    friend constexpr Point<F> operator*(const Point &a, F k) {
        return {a.x * k, a.y * k};
    }
    template<class F>
    friend constexpr Point<F> operator/(const Point &a, F k) {
        assert(sgn(k) != 0);
        return {a.x / k, a.y / k};
    }
    constexpr Point operator*=(T k) {
        *this = *this * k;
        return *this;
    }
    constexpr Point operator/=(T k) {
        *this = *this / k;
        return *this;
    }
    friend constexpr Point operator+(const Point &a, const Point &b) {
        return Point(a.x + b.x, a.y + b.y);
    }
    friend constexpr Point operator-(const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }
    constexpr Point operator+=(const Point &b) {
        *this = *this + b;
        return *this;
    }
    constexpr Point operator-=(const Point &b) {
        *this = *this - b;
        return *this;
    }
    friend constexpr T dot(const Point &a, const Point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend constexpr T cross(const Point &a, const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend constexpr T abs2(const Point &p) {
        return p.x * p.x + p.y * p.y;
    }
    friend constexpr double abs(const Point &p) {
        return std::sqrt(abs2(p));
    }
    friend constexpr bool operator<(const Point &a, const Point &b) {
        return sgn(a.x - b.x) == 0 ? a.y < b.y : a.x < b.x;
    }
    friend constexpr bool operator==(const Point &a, const Point &b) {
        return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Point &p) {
        is >> p.x >> p.y;
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};
Point<double> rotate(const Point<double> &p, double t) {
    return {p.x * std::cos(t) - p.y * std::sin(t), p.x * std::sin(t) + p.y * std::cos(t)};
}

// Line
template<typename T>
struct Line {
    Point<T> a;
    Point<T> b;

    constexpr Line() : a{}, b{} {}
    template<typename F>
    constexpr Line(const Point<F> &_a, const Point<F> &_b) : a(_a), b(_b) {}
    template<typename F>
    constexpr Line(const Line<F> &l) : a(l.a), b(l.b) {}

    friend constexpr Point<T> vec(const Line &l) {
        return l.b - l.a;
    }
    // false:out  true:on
    friend constexpr bool pointOnLine(const Point<T> &x, const Line &s) {
        return sgn(cross(x - s.a, vec(s))) == 0;
    }
    // 0:out  1:endpoints  2:on
    friend constexpr int pointOnSegment(const Point<T> &x, const Line &s) {
        if (x == s.a || x == s.b) {
            return 1;
        }
        if (sgn(cross(x - s.a, vec(s))) == 0 && sgn(dot(x - s.a, x - s.b)) < 0) {
            return 2;
        }
        return 0;
    }
};
double pointLineDist(const Point<double> &p, const Line<double> &l){
    if (l.a == l.b) {
        return abs(p - l.a);
    }
    return std::abs(cross(p - l.a, vec(l))) / abs(vec(l));
}
Point<double> intersection(const Line<double> &l1, const Line<double> &l2) {
    assert(sgn(cross(vec(l1), vec(l2))) != 0);
    return l1.a + vec(l1) * cross(l2.a - l1.a, vec(l2)) / cross(vec(l1), vec(l2));
}

// Polygon
// 0:out  1:on  2:in
// Polygon vertexes in counter-clockwise order.
template<typename T>
constexpr int pointInConvex(const Point<T> &x, const std::vector<Point<T>> &a) {
    int n = a.size();
    if (sgn(cross(a[1] - a[0], x - a[0])) < 0 || sgn(cross(a[n - 1] - a[0], x - a[0])) > 0) {
        return 0;
    }
    int lo = 1, hi = n - 1;
    while (lo < hi) {
        int m = (lo + hi) / 2;
        if (sgn(cross(a[m + 1] - a[0], x - a[0])) >= 0) {
            lo = m + 1;
        } else {
            hi = m;
        }
    }
    if (lo == n - 1) {
        return sgn(dot(x - a[0], x - a[lo])) <= 0;
    }
    if (sgn(cross(a[lo + 1] - a[lo], x - a[lo])) == 0 || lo == 1 && pointOnSegment(x, {a[0], a[lo]})) {
        return 1;
    }
    if (sgn(cross(a[lo + 1] - a[lo], x - a[lo])) > 0) {
        return 2;
    }
    return 0;
}