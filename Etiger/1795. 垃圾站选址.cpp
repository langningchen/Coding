#include <bits/stdc++.h>
using namespace std;
const int N = 100009;
vector<int> to[N];
int n, m;
int d[N], f[N], sz[N], tI[N], tO[N], euler[N * 2], timer;
void dfs_d_sz(int u, int fa) {
    sz[u] = 1;
    d[u] = d[fa] + 1;
    for (int i = 0; i < to[u].size(); i++) {
        int v = to[u][i];
        if (v == fa)
            continue;
        dfs_d_sz(v, u);
        sz[u] += sz[v];
    }
}
void dfs_f(int u, int fa) {
    for (int i = 0; i < to[u].size(); i++) {
        int v = to[u][i];
        if (v == fa) continue;
        f[v] = f[u] - sz[v] + (n - sz[v]);
        dfs_f(v, u);
    }
}
void solve() {
    dfs_d_sz(1, 0);
    for (int u = 1; u <= n; u++) f[1] += d[u] - 1;
    dfs_f(1, 0);
    int id = max_element(f + 1, f + 1 + n) - f;
    cout << id << endl;
}
int main() {
    freopen("dumpster.in", "r", stdin);
    freopen("dumpster.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    solve();
    return 0;
}
