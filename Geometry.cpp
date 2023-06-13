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

template<typename T>
struct Point {
    T x;
    T y;
    constexpr Point() : x{}, y{} {}
    template<typename U>
    constexpr Point(U x_ = 0, U y_ = 0) : x{x_}, y{y_} {}
    template<typename U>
    constexpr Point(Point<U> p_) : x{p_.x}, y{p_.y} {}

    constexpr Point &operator+=(Point p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    constexpr Point &operator-=(Point p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    constexpr Point &operator*=(T v) & {
        x *= v;
        y *= v;
        return *this;
    }
    constexpr Point &operator/=(T v) & {
        assert(sgn(v) != 0);
        x /= v;
        y /= v;
        return *this;
    }
    constexpr Point operator-() const {
        return {-x, -y};
    }
    friend constexpr Point operator+(Point a, Point b) {
        return a += b;
    }
    friend constexpr Point operator-(Point a, Point b) {
        return a -= b;
    }
    friend constexpr Point operator*(Point a, T b) {
        return a *= b;
    }
    friend constexpr Point operator*(T a, Point b) {
        return b *= a;
    }
    friend constexpr Point operator/(Point a, T b) {
        return a /= b;
    }
    friend constexpr bool operator==(Point a, Point b) {
        return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<typename T>
constexpr T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}
 
template<typename T>
constexpr T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template<typename T>
T square(Point<T> p) {
    return dot(p, p);
}
 
template<typename T>
double length(Point<T> p) {
    return std::sqrt(double(square(p)));
}

template<typename T>
constexpr Point<T> rotate(Point<T> p) {
    return {-p.y, p.x};
}

constexpr Point<double> rotate(Point<double> p, double t) {
    return {p.x * std::cos(t) - p.y * std::sin(t), p.x * std::sin(t) + p.y * std::cos(t)};
}

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    constexpr Line() : a{}, b{} {}
    template<typename U>
    constexpr Line(Point<U> a_, Point<U> b_) : a{a_}, b{b_} {}
    template<typename U>
    constexpr Line(Line<U> l_) : a{l_.a}, b{l_.a} {}
};

template<class T>
bool pointOnLineLeft(Point<T> p, Line<T> l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

template<typename T>
constexpr bool pointOnSegment(Point<T> p, Line<T> l) {
    return cross(p - l.a, l.b - l.a) == 0 && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
        && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}

template<typename T>
constexpr Point<T> lineIntersection(Line<T> l1, Line<T> l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
template<typename T>
std::tuple<int, Point<T>, Point<T>> segmentIntersection(Line<T> l1, Line<T> l2) {
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, Point<T>(), Point<T>()};
        } else {
            auto maxx1 = std::max(l1.a.x, l1.b.x);
            auto minx1 = std::min(l1.a.x, l1.b.x);
            auto maxy1 = std::max(l1.a.y, l1.b.y);
            auto miny1 = std::min(l1.a.y, l1.b.y);
            auto maxx2 = std::max(l2.a.x, l2.b.x);
            auto minx2 = std::min(l2.a.x, l2.b.x);
            auto maxy2 = std::max(l2.a.y, l2.b.y);
            auto miny2 = std::min(l2.a.y, l2.b.y);
            Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
            Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    
    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0)) {
        return {0, Point<T>(), Point<T>()};
    }
    
    Point p = lineIntersection(l1, l2);
    if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}
template<typename T>
constexpr bool pointInPolygon(Point<T> a, std::vector<Point<T>> &p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }
    return t == 1;
}

// counter-clockwise order
// 0 : outside
// 1 : on side
// 2 : inside
template<typename T>
constexpr int pointInConvex(Point<T> x, std::vector<Point<T>> &a) {
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

template<typename T>
constexpr T pointLineDistance(Point<T> p, Line<T> l){
    if (l.a == l.b) {
        return length(p - l.a);
    }
    return std::abs(cross(p - l.a, l.b - l.a)) / length(l.b - l.a);
}