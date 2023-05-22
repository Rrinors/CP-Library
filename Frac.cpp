int sgn(const Frac &f) {
    if (f.x == 0) {
        return 0;
    }
    if ((f.x > 0) == (f.y > 0)) {
        return 1;
    }
    return -1;
}
struct Frac {
    i64 x, y;
    Frac(i64 x = 0, i64 y = 1) {
        assert(y != 0);
        i64 g = std::gcd(x, y);
        this->x = x / g;
        this->y = y / g;
    }

    friend Frac operator+(const Frac &lhs, const Frac &rhs) {
        return {lhs.x * rhs.y + lhs.y * rhs.x, lhs.y * rhs.y};
    }
    friend Frac operator-(const Frac &lhs, const Frac &rhs) {
        return {lhs.x * rhs.y - lhs.y * rhs.x, lhs.y * rhs.y};
    }
    friend Frac operator*(const Frac &lhs, const Frac &rhs) {
        return Frac(lhs.x * rhs.x, lhs.y * rhs.y);
    }
    friend Frac operator/(const Frac &lhs, const Frac &rhs) {
        return Frac(lhs.x * rhs.y, lhs.y * rhs.x);
    }
    Frac &operator+=(const Frac &rhs) {
        return *this = *this + rhs;
    }
    Frac &operator-=(const Frac &rhs) {
        return *this = *this - rhs;
    }
    Frac &operator*=(const Frac &rhs) {
        return *this = *this * rhs;
    }
    Frac &operator/=(const Frac &rhs) {
        return *this = *this / rhs;
    }
    friend bool operator<(const Frac &lhs, const Frac &rhs) {
        if (sgn(lhs) != sgn(rhs)) {
            return sgn(lhs) < sgn(rhs);
        }
        if (sgn(lhs) >= 0 && sgn(rhs) >= 0) {
            return abs(lhs.x * rhs.y) < abs(lhs.y * rhs.x);
        }
        return abs(lhs.x * rhs.y) > abs(lhs.y * rhs.x);
    }
    friend bool operator==(const Frac &lhs, const Frac &rhs) {
        return sgn(lhs) == sgn(rhs) && abs(lhs.x) == abs(rhs.x) && abs(lhs.y) == abs(rhs.y);
    }
};