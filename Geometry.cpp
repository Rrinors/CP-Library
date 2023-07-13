template<class T>
constexpr T eps;

template<>
constexpr int eps<int> = 0;

template<>
constexpr i64 eps<i64> = 0;

template<>
constexpr double eps<double> = 1E-6;

template<class T>
constexpr int sgn(T x) {
    if (x > eps<T>) {
        return 1;
    }
    if (x < eps<T>) {
        return -1;
    }
    return 0;
}

template<class T>
struct Point {
    T x;
    T y;
    constexpr Point() : x{}, y{} {}
    template<class U>
    constexpr Point(U x_ = 0, U y_ = 0) : x{x_}, y{y_} {}
    template<class U>
    explicit constexpr Point(Point<U> p_) : x{T(p_.x)}, y{T(p_.y)} {}

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
    friend constexpr bool operator<(Point a, Point b) {
        return sgn(a.x - b.x) == 0 ? a.y < b.y : a.x < b.x;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
constexpr T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}
 
template<class T>
constexpr T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
constexpr T square(Point<T> p) {
    return dot(p, p);
}
 
template<class T>
constexpr double length(Point<T> p) {
    return std::sqrt(square(p));
}

template<class T>
constexpr Point<T> vertical(Point<T> p) {
    return {-p.y, p.x};
}

template<class T>
constexpr Point<double> rotate(Point<T> p, double t) {
    return {p.x * std::cos(t) - p.y * std::sin(t), p.x * std::sin(t) + p.y * std::cos(t)};
}

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    constexpr Line() : a{}, b{} {}
    template<class U>
    constexpr Line(Point<U> a_, Point<U> b_) : a{a_}, b{b_} {}
    template<class U>
    explicit constexpr Line(Line<U> l_) : a{Point<T>(l_.a)}, b{Point<T>(l_.a)} {}

    friend constexpr std::ostream &operator<<(std::ostream &os, Line l) {
        return os << l.a << " -- " << l.b;
    }
};

template<class T>
constexpr bool pointOnLineLeft(Point<T> p, Line<T> l) {
    return sgn(cross(l.b - l.a, p - l.a)) > 0;
}

template<class T>
constexpr bool pointOnSegment(Point<T> p, Line<T> l) {
    return sgn(cross(p - l.a, l.b - l.a)) == 0 && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
        && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}

template<class T>
constexpr Point<T> lineIntersection(Line<T> l1, Line<T> l2) {
    return l1.a + (l1.b - l1.a) * cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b);
}

template<class T>
constexpr T pointLineDistance(Point<T> p, Line<T> l){
    if (l.a == l.b) {
        return length(p - l.a);
    }
    return std::abs(cross(p - l.a, l.b - l.a)) / length(l.b - l.a);
}

// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
template<class T>
constexpr std::tuple<int, Point<T>, Point<T>> segmentIntersection(Line<T> l1, Line<T> l2) {
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
    if (sgn(cross(l1.b - l1.a, l2.b - l2.a)) == 0) {
        if (sgn(cross(l1.b - l1.a, l2.a - l1.a)) != 0) {
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
    auto cp1 = sgn(cross(l2.a - l1.a, l2.b - l1.a));
    auto cp2 = sgn(cross(l2.a - l1.b, l2.b - l1.b));
    auto cp3 = sgn(cross(l1.a - l2.a, l1.b - l2.a));
    auto cp4 = sgn(cross(l1.a - l2.b, l1.b - l2.b));
    
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

template<class T>
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
// 0 : out
// 1 : on
// 2 : in
template<class T>
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

template<class T>
constexpr bool segmentInPolygon(Line<T> l, std::vector<Point<T>> &p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) {
        return false;
    }
    if (!pointInPolygon(l.b, p)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, Line(u, v));
        
        if (t == 1) {
            return false;
        }
        if (t == 0) {
            continue;
        }
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b) {
                if (cross(v - u, w - v) > 0) {
                    return false;
                }
            }
        } else {
            if (p1 != u && p1 != v) {
                if (pointOnLineLeft(l.a, Line(v, u))
                    || pointOnLineLeft(l.b, Line(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l)
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, Line(l.b, l.a))) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}