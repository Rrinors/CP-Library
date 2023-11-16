bool Q;
struct Line {
    i64 x, y;
    mutable i64 k;
};

bool operator<(Line a, Line b) {
    return Q ? a.k < b.k : a.x < b.x;
}

struct LineContainer : std::multiset<Line> {
    static constexpr i64 inf = 1E18;

    i64 div(i64 a, i64 b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool isect(auto a, auto b) {
        if (b == end()) {
            a->k = inf;
            return false;
        }
        if (a->x == b->x) {
            a->k = a->y < b->y ? inf : -inf;
        } else {
            a->k = div(b->y - a->y, b->x - a->x);
        }
        return a->k >= b->k;
    }

    void add(i64 x, i64 y) {
        auto it = insert({x, y});
        while (isect(it, std::next(it))) {
            erase(std::next(it));
        }
        if (it == begin()) {
            return;
        }
        if (isect(std::prev(it), it)) {
            it = erase(it);
            isect(std::prev(it), it);
        } else {
            it--;
            while (it != begin() && std::prev(it)->k >= it->k) {
                it = erase(it);
                isect(std::prev(it), it);
                it--;
            }
        }
    }

    std::pair<i64, i64> query(i64 k) {
        Q = true;
        auto it = lower_bound({0, 0, k});
        Q = false;
        return {it->x, it->y};
    }
};