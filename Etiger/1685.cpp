#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, f[N], h1[N], h2[N];
vector<int> to[N];
void dfs_h1h2(int u, int fa)
{
    h1[u] = h2[u] = 0;
    for (int i = 0; i < to[u].size(); i++)
    {
        int v = to[u][i];
        if (v == fa)
            continue;
        dfs_h1h2(v, u);
        h2[u] = max(h2[u], h1[v] + 1);
        if (h2[u] > h1[u])
            swap(h2[u], h1[u]);
    }
}
void input()
{
    cin >> n;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
}
void solve()
{
    dfs_h1h2(1, 0);
    for (int u = 1; u <= n; u++)
        f[u] = h1[u] + h2[u];
    int ans = *max_element(f + 1, f + 1 + n);
    cout << ans << endl;
}
int main()
{
    freopen("diameter.in", "r", stdin);
    freopen("diameter.out", "w", stdout);
    input();
    solve();
    return 0;
}
