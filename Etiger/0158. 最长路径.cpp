#include <bits/stdc++.h>
using namespace std;
const int N = 1505;
const int INF = 9999999999;
int m, n, ok[N], f[N];
vector<int> to[N];
vector<int> w[N];
int F(int u) {
    if (ok[u]) return f[u];
    ok[u] = 1;
    for (int i = 0; i < to[u].size(); i++) {
        int v = to[u][i];
        int cost = w[u][i];
        if (F(v) != -INF)
           f[u] = max(f[u], f[v] + cost);
    }
    return f[u];
}
int main() {
//    freopen("longest.in","r",stdin);
//    freopen("longest.out","w",stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        to[u].push_back(v);
        w[u].push_back(cost);
    }
    for (int u = 1; u <= n; u++) f[u] = -INF;
    ok[n] = 1; f[n] = 0;
    if (F(1) == -INF)
        cout << -1 << endl;
    else
        cout << f[1] << endl;
    return 0;
}



