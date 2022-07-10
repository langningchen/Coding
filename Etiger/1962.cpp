#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, q, L;
int d[N], p[N][21];
int timer, tI[N], tO[N];
struct edge {
    int to, nxt;
} e[N * 2];
int nE, hd[N];
void addE(int u, int v) {
    e[++nE].to = v;
    e[nE].nxt = hd[u];
    hd[u] = nE;
    e[++nE].to = u;
    e[nE].nxt = hd[v];
    hd[v] = nE;
}
void dfs(int u, int fa) {
    tI[u] = ++timer;
    d[u] = d[fa] + 1;
    p[u][0] = fa;
    for (int i = 1; i <= L; i++) {
        p[u][i] = p[p[u][i - 1]][i - 1];
    }
    for (int i = hd[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u);
    }
    tO[u] = ++timer;
}
bool up(int u, int v) {
    return !u || tI[u] <= tI[v] && tO[v] <= tO[u];
}
int lca(int u, int v) {
    if (up(u, v)) return u;
    if (up(v, u)) return v;
    for (int i = L; i >= 0; i--) {
        if (!up(p[u][i], v)) {
            u = p[u][i];
        }
    }
    return p[u][0];
}
int dst(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
}
bool onPath(int x, int u, int v) {
    return dst(u, x) + dst(v, x) == dst(u, v);
}
int main() {
    freopen("intersection.in", "r", stdin);
    freopen("intersection.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        addE(u, v);
    }
    L = log(n) / log(2) + 1;
    dfs(1, 0);
    int ans = 0;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        int uv = lca(u, v);
        int ab = lca(a, b);
        if (d[ab] > d[uv]) {
            ans += onPath(ab, u, v);
        }
        else {
            ans += onPath(uv, a, b);
        }
    }
    cout << ans << endl;
    return 0;
}