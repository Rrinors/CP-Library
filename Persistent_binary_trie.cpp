
constexpr int N = 600010;

int tot = 0;
int trie[25 * N][2], val[25 * N];

void append(int &p, int o, int v) {
    p = ++tot;
    int x = p;
    for (int i = 23; i >= 0; i--) {
        val[x] = val[o] + 1;
        int t = v >> i & 1;
        trie[x][t] = ++tot;
        trie[x][!t] = trie[o][!t];
        x = trie[x][t];
        o = trie[o][t];
    }
    val[x] = val[o] + 1;
}

int query(int p, int q, int v) {
    int ans = 0;
    for (int i = 23; i >= 0; i--) {
        int t = v >> i & 1;
        if (val[trie[q][!t]] - val[trie[p][!t]]) {
            ans += 1 << i;
            p = trie[p][!t];
            q = trie[q][!t];
        } else {
            p = trie[p][t];
            q = trie[q][t];
        }
    }
    return ans;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> rt(n + 1);
    for (int i = 0; i < n; i++) {
        if (i) {
            a[i] ^= a[i - 1];
        }
        append(rt[i + 1], rt[i], a[i]);
    }

    while (m--) {
        char o;
        std::cin >> o;
        if (o == 'A') {
            n++;
            a.resize(n);
            std::cin >> a[n - 1];
            a[n - 1] ^= a[n - 2];
            rt.resize(n + 1);
            append(rt[n], rt[n - 1], a[n - 1]);
        } else {
            int l, r, x;
            std::cin >> l >> r >> x;
            l--, r--;
            int ans = query(rt[max(0, l - 1)], rt[r], x ^ a[n - 1]);
            if (!l) {
                ans = std::max(ans, a[n - 1] ^ x);
            }
            cout << ans << "\n";
        }
    }

    return 0;
}