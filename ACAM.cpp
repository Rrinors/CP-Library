constexpr int N = 1000000;

int tot;
int trie[N][26], fail[N], cnt[N];

int newNode() {
    tot++;
    std::fill(trie[tot], trie[tot] + 26, 0);
    fail[tot] = cnt[tot] = 0;
    return tot;
}

void insert(std::std::string &s) {
    int p = 0;
    for (auto x : s) {
        if (!trie[p][x - 'a']) {
            trie[p][x - 'a'] = newNode();
        }
        p = trie[p][x - 'a'];
    }
    cnt[p]++;
}

void work() {
    std::queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (trie[u][i]) {
                if (u) {
                    fail[trie[u][i]] = trie[fail[u]][i];
                }
                q.push(trie[u][i]);
            } else {
                trie[u][i] = trie[fail[u]][i];
            }
        }
    }
}

int match(std::string &s) {
    int u = 0, ans = 0;
    for (auto x : s) {
        u = trie[u][x - 'a'];
        for (int v = u; v && cnt[v] != -1; v = fail[v]) {
            ans += cnt[v];
            cnt[v] = -1;
        }
    }
    return ans;
}