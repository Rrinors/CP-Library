struct Frac {
    i64 x, y;

    Frac() : x{0}, y{1} {}
    Frac(i64 x, i64 y = 1) {
        assert(y != 0);
        if (y < 0) {
            x = -x;
            y = -y;
        }
        this->x = x;
        this->y = y;
    }

    void norm() {
        i64 g = std::gcd(x, y);
        x /= g;
        y /= g;
    }

    Frac operator-() const {
        return {-x, -y};
    }
    Frac &operator+=(Frac a) & {
        return *this = {x * a.y + y * a.x, y * a.y};
    }
    Frac &operator-=(Frac a) & {
        return *this = {x * a.y - y * a.x, y * a.y};
    }
    Frac &operator*=(Frac a) & {
        return *this = {x * a.x, y * a.y};
    }
    Frac &operator/=(Frac a) & {
        return *this = {x * a.y, y * a.x};
    }
    friend Frac operator+(Frac a, Frac b) {
        return a += b;
    }
    friend Frac operator-(Frac a, Frac b) {
        return a -= b;
    }
    friend Frac operator*(Frac a, Frac b) {
        return a *= b;
    }
    friend Frac operator/(Frac a, Frac b) {
        return a /= b;
    }
    friend bool operator==(Frac a, Frac b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator<(Frac a, Frac b) {
        if ((a.x > 0) ^ (b.x > 0)) {
            return a.x < b.x;
        }
        return a.x * b.y < a.y * b.x;
    }
    friend std::ostream &operator<<(std::ostream &os, Frac a) {
        a.norm();
        return os << a.x << "/" << a.y;
    }
};