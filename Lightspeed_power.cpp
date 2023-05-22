
constexpr int P = 998244353;

std::vector<i64> p1, p2;
int s;

void work(int a, int n) {
    s = std::sqrt(P) + 1;
    p1.resize(s + 1);
    p2.resize(n / s + 1);
    
    p1[0] = 1;
    for (int i = 1; i <= s; i++) {
        p1[i] = p1[i - 1] * a % P;
    }
    p2[0] = 1;
    
    for (int i = 1; i <= n / s; i++) {
        p2[i] = p2[i - 1] * p1[s] % P;
    }
}

int calc(int b) {
    if (b <= s) {
        return p1[b];
    } else {
        int k = b / s;
        return p2[k] * p1[b - k * s] % P;
    }
}