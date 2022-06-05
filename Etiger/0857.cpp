#include <bits/stdc++.h>
using namespace std;
const int N = 200009;
vector<long long> son[N];
int L, n, m, d[N], p[N][30], st[N][30];
void dfs(int u) {
    d[u] = d[p[u][0]] + 1;
    for (int i = 1; i <= L; i++) {
        p[u][i] = p[p[u][i - 1]][i - 1];
        st[u][i] = max(st[u][i - 1], st[p[u][i - 1]][i - 1]);
    }
    for (int i = 0; i < son[u].size(); i++)
        dfs(son[u][i]);
}
int query(int u, int k) {
    int ans = st[u][0];
    for (int i = 0; i <= L; i++)
        if ((1 << i) & k) {
            ans = max(ans, st[p[u][0]][i]);
            u = p[u][i];
        }
    return ans;
}
int main() {
    freopen("rich.in", "r", stdin);
    freopen("rich.out", "w", stdout);
    cin >> n >> m;
    for (int u = 2; u <= n; u++) {
        cin >> p[u][0];
        son[p[u][0]].push_back(u);
    }
    for (int u = 1; u <= n; u++) cin >> st[u][0];
    L = log(n) / log(2) + 1;
    dfs(1);
    for (int i = 1; i <= m; i++) {
        int x, k;
        cin >> x >> k;
        k = min(k, d[x] - 1);
        cout << query(x, k) << endl;
    }
    return 0;
}
