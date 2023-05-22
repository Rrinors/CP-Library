std::array<i64, 3> exgcd(i64 a, i64 b) {
    if (!b) {
        return {a, 1, 0};
    }
    auto [g, x, y] = exgcd(b, a % b);
    return {g, y, x - a / b * y};
}

void solve() {
    int a, b, c;
    std::cin >> a >> b >> c;

    auto [d, x, y] = exgcd(a, b);

    if (c % d) {
        std::cout << "-1\n";
        return;
    }
    
    x *= c / d;
    y *= c / d;
    i64 dx = b / d;
    i64 dy = a / d;

    i64 x0 = x <= 0 ? x + (dx - x) / dx * dx : x - (x - 1) / dx * dx;
    i64 y1 = (c - a * x0) / b;
    if (y1 > 0) {
        i64 y0 = y <= 0 ? y + (dy - y) / dy * dy : y - (y - 1) / dy * dy;
        i64 x1 = (c - b * y0) / a;
        std::cout << (y1 - 1) / dy + 1 << " " << x0 << " " << y0 << " " << x1 << " " << y1 << "\n";
    } else {
        i64 y0 = y <= 0 ? y + (dy - y) / dy * dy : y - (y - 1) / dy * dy;
        std::cout << x0 << " " << y0 << "\n";
    }
}