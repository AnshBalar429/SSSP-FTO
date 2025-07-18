#include <bits/stdc++.h>

static constexpr double ALPHA = 0.5; // pick α ∈ (0, 1/2]
void Numerator() {
    int n, m, s;
    std::cin >> n >> m >> s;
    s--;

    struct Edge {
        int u, v;
    };

    std::vector<std::vector<int>> graph(n);
    std::vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back({u, v});
    }

    const int INF = INT_MAX / 2;
    // 1) BFS from source to build dist0 and parent pointers
    std::vector<int> dist0(n, INF), parent(n, -1);
    std::deque<int> dq;
    dist0[s] = 0;
    dq.push_back(s);
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (int v : graph[u]) {
            if (dist0[v] > dist0[u] + 1) {
                dist0[v] = dist0[u] + 1;
                parent[v] = u;
                dq.push_back(v);
            }
        }
    }

    // Build BFS tree adjacency for LCA
    std::vector<std::vector<int>> tree(n);
    for (int v = 0; v < n; v++) {
        if (parent[v] >= 0) tree[parent[v]].push_back(v);
    }

    // 2) LCA preprocessing: tin/tout + binary lifting
    int LOG = 1;
    while ((1 << LOG) <= n) LOG++;
    std::vector<std::vector<int>> up(LOG, std::vector<int>(n, -1));
    std::vector<int> depth(n), tin(n), tout(n);
    int timer = 0;
    std::function<void(int,int)> dfs = [&](int u, int p) {
        tin[u] = timer++;
        up[0][u] = p;
        for (int k = 1; k < LOG; k++) {
            int pp = up[k-1][u];
            up[k][u] = (pp < 0 ? -1 : up[k-1][pp]);
        }
        for (int v : tree[u]) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
        tout[u] = timer++;
    };
    dfs(s, -1);

    auto isAncestor = [&](int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    };

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(25);
    int64_t t = 1;
    // std::cin >> t;
    while (t-- > 0) {
        Numerator();
    }
    return 0;
}