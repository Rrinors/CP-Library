#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1000000;
constexpr int inf = 0x7fffffff;

struct Tag {
    int x = inf;
    Tag() : x(inf) {}
    Tag(int x) : x(x) {}

    void apply(Tag b) {
        if (b.x < x) {
            x = b.x;
        }
    }
} tag[4 * N];

struct Info {
    int x;
    int y;
    int cnt;
    i64 sum;
    Info() : x(0), y(-1), cnt(0), sum(0) {}
    Info(int x, int y, int cnt, i64 sum) : x(x), y(y), cnt(cnt), sum(sum) {}

    void apply(Tag b) {
        if (b.x < x) {
            sum -= 1LL * (x - b.x) * cnt;
            x = b.x;
        }
    }
} info[4 * N];

Info operator+(Info a, Info b) {
    Info c;
    c.x = std::max(a.x, b.x);
    c.y = std::max(a.y, b.y);
    if (a.x != b.x) {
        c.y = std::max(c.y, std::min(a.x, b.x));
    }
    if (a.x < b.x) {
        c.cnt = b.cnt;
    } else if (a.x > b.x) {
        c.cnt = a.cnt;
    } else {
        c.cnt = a.cnt + b.cnt;
    }
    c.sum = a.sum + b.sum;
    return c;
}

void pull(int p) {
    info[p] = info[2 * p] + info[2 * p + 1];
}

void build(int p, int l, int r, auto &a) {
    tag[p] = Tag();
    if (l == r) {
        info[p] = {a[l], -1, 1, a[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * p, l, m, a);
    build(2 * p + 1, m + 1, r, a);
    pull(p);
}

void apply(int p, Tag v) {
    info[p].apply(v);
    tag[p].apply(v);
}

void push(int p) {
    apply(2 * p, tag[p]);
    apply(2 * p + 1, tag[p]);
    tag[p] = Tag();
}

void rangeApply(int p, int l, int r, int x, int y, int t) {
    if (info[p].x <= t) {
        return;
    }
    if (x <= l && r <= y && info[p].y < t) {
        apply(p, t);
        return;
    }
    push(p);
    int m = (l + r) / 2;
    if (m >= x) rangeApply(2 * p, l, m, x, y, t); 
    if (m < y) rangeApply(2 * p + 1, m + 1, r, x, y, t);
    pull(p);
}

Info rangeQuery(int p, int l, int r, int x, int y) {
    if (r < x || y < l) {
        return Info();
    }
    if (x <= l && r <= y) {
        return info[p];
    }
    push(p);
    int m = (l + r) / 2;
    return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
}

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    build(1, 0, n - 1, a);
    while (m--) {
        int op, x, y;
        std::cin >> op >> x >> y;
        x--, y--;
        if (op == 0) {
            int t;
            std::cin >> t;
            rangeApply(1, 0, n - 1, x, y, t);
        } else {
            auto ans = rangeQuery(1, 0, n - 1, x, y);
            if (op == 1) {
                std::cout << ans.x << "\n";
            } else {
                std::cout << ans.sum << "\n";
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }   
    
    return 0;
}