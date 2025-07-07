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