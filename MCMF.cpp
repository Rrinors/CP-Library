template<class T, class U>
struct MCMF {
    const int n;
    struct Edge {
        int to;
        T cap;
        U cost;
        Edge(int to, T cap, U cost) : to(to), cap(cap), cost(cost) {}
    };
    std::vector<std::vector<int>> g;
    std::vector<Edge> e;
    std::vector<U> dis;
    std::vector<int> p;
    std::vector<bool> vis;
    MCMF(int n) : n(n), g(n), vis(n) {}

    void addEdge(int u, int v, T cap, U cost) {
        g[u].push_back(e.size());
        e.emplace_back(v, cap, cost);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -cost);
    }
    U spfa(int s, int t) {
        dis.assign(n, std::numeric_limits<U>::max());
        p.assign(n, -1);
        std::queue<int> q;
        q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            vis[u] = false;
            for (int i : g[u]) {
                auto [v, c, w] = e[i];
                if (c > 0 && dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    p[v] = i;
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        return dis[t];
    }
    std::pair<T, U> work(int s, int t) {
        T maxFlow = 0;
        U minCost = 0;
        for (U d = spfa(s, t); d != std::numeric_limits<U>::max(); d = spfa(s, t)) {
            T x = std::numeric_limits<T>::max();
            for (int i = p[t]; i != -1; i = p[e[i ^ 1].to]) {
                x = std::min(x, e[i].cap);
            }
            for (int i = p[t]; i != -1; i = p[e[i ^ 1].to]) {
                e[i].cap -= x;
                e[i ^ 1].cap += x;
            }
            maxFlow += x;
            minCost += d * x;
        }
        return {maxFlow, minCost};
    }
};