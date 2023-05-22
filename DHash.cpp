struct DHash {
    static constexpr int P1 = 1000000829;
    static constexpr int P2 = 1000000579;
    i64 x, y;
    constexpr DHash(i64 x, i64 y) : x(x % P1), y(y % P2) {}
    constexpr DHash(i64 x = 0) : x(x % P1), y(x % P2) {}
 
    DHash &operator+=(const DHash &rhs) {
        x = (x + rhs.x) % P1;
        y = (y + rhs.y) % P2;
        return *this;
    }
    DHash &operator-=(const DHash &rhs) {
        x = (x - rhs.x + P1) % P1;
        y = (y - rhs.y + P2) % P2;
        return *this;
    }
    DHash &operator*=(const DHash &rhs) {
        x = x * rhs.x % P1;
        y = y * rhs.y % P2;
        return *this;
    }
    friend DHash operator+(const DHash &lhs, const DHash &rhs) {
        DHash res = lhs;
        res += rhs;
        return res;
    }
    friend DHash operator-(const DHash &lhs, const DHash &rhs) {
        DHash res = lhs;
        res -= rhs;
        return res;
    }
    friend DHash operator*(const DHash &lhs, const DHash &rhs) {
        DHash res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr bool operator==(const DHash &lhs, const DHash &rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend constexpr bool operator<(const DHash &lhs, const DHash &rhs) {
        return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
    }
};


DHash get(int l, int r) {
    if (l > r) {
        return DHash();
    }
    return h[r] - h[l - 1] * pw[r - l + 1];
};