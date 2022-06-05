#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
vector<int> es[N];
int n, p[N], f[N], sz[N], g[N];
void dfs(int u, int fa) {
    p[u] = fa;
    sz[u] = 1;
    for (int i = 0; i < es[u].size(); i++) {
        int v = es[u][i];
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
int main() {
    freopen("bomb5.in", "r", stdin);
    freopen("bomb5.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        cin >> x >> y;
        es[x].push_back(y);
        es[y].push_back(x);
    }
    dfs(1, 0);
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < es[u].size(); i++) {
            int v = es[u][i];
            if (v == p[u]) continue;
            f[u] = max(f[u], sz[v]);
        }
         f[u] = max(f[u], n - sz[u]);
    }
    int id = min_element(f + 1, f + 1 + n) - f;
    cout << id << " " << f[id] << endl;
    return 0;
}
