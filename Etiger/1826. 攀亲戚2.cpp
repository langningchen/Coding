#include <bits/stdc++.h>
using namespace std;
const int N = 200009;
vector<int> to[N];
int L, n, q, p[N][20];
int tI[N], tO[N], timer;
void dfs(int u, int fa) {
    tI[u] = timer++;
    p[u][0] = fa;
    for (int i = 1; i <= L; i++)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = 0; i < to[u].size(); i++)
        if (to[u][i] != fa) dfs(to[u][i], u);
    tO[u] = ++timer;
}
bool up(int u, int v) {
    return !u || tI[u] <= tI[v] && tO[v] <= tO[u];
}
int lca(int u, int v) {
    if (up(u, v)) return u;
    if (up(v, u)) return v;
    for (int i = L; i >= 0; i--)
        if (!up(p[u][i], v))
            u = p[u][i];
    return p[u][0];
}
int main() {
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    L = log(n) / log(2) + 1;
    dfs(1, 0);
    long long ans = 0;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int x, k;
        cin >> x >> k;
        ans += lca(x, k);
    }
    cout << ans << endl;
    return 0;
}
