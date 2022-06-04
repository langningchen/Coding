#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, g[N], f[N], h1[N], h2[N];
vector<int> to[N];
void dfs_h1h2(int u, int fa) {
    for (int i = 0; i < to[u].size(); i++) {
        int v = to[u][i];
        if (v == fa) continue;
        dfs_h1h2(v, u);
        h2[u] = max(h2[u], h1[v] + 1);
        if (h2[u] > h1[u]) swap(h2[u], h1[u]);
    } 
}
void dfs_g(int u, int fa) {
    for (int i = 0; i < to[u].size(); i++) {
        int v = to[u][i];
        if (v == fa) continue;
        if (h1[u] == h1[v] + 1)
            g[v] = 1 + max(g[u], h2[u]);
        else
            g[v] = 1 + max(g[u], h1[u]);
        dfs_g(v, u);
    }
}
void input() {
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v; cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
}
void solve() {
    dfs_h1h2(1, 0);
    dfs_g(1, 0);
    for (int u = 1; u <= n; u++)
        cout << max(g[u], h1[u]) << endl;
}
int main() {
    input();
    solve();
    return 0;
}
