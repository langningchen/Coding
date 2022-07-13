#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int u, v, n, t, x, y, z, d[N], p[N];
vector<int> to[N];
void dfs(int u, int fa)
{
    p[u] = fa;
    d[u] = d[fa] + 1;
    for (int i = 0; i < to[u].size(); i++)
    {
        int v = to[u][i];
        if (v == fa)
            continue;
        dfs(v, u);
    }
}
int lca(int u, int v)
{
    while (d[u] > d[v])
        u = p[u];
    while (d[v] > d[u])
        v = p[v];
    while (u != v)
        u = p[u], v = p[v];
    return u;
}
int dst(int u, int v)
{
    return d[u] + d[v] - 2 * d[lca(u, v)];
}
int main()
{
    cin >> n >> t;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 0; i < t; i++)
    {
        cin >> x >> y >> z;
        cout << dst(x, y) << endl;
    }
    return 0;
}
