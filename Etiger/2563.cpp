#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
struct
{
    int to, nxt;
} e[N * 2];
int n, m, d[N], p[N], sz[N], son[N], top[N], hd[N], id[N];
void dfs_son(int u, int fa)
{
    d[u] = d[fa] + 1;
    p[u] = fa;
    sz[u] = 1;
    son[u] = 0;
    for (int i = hd[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa)
            continue;
        dfs_son(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v] ||
            (sz[son[u]] == sz[v] && v < son[u]))
            son[u] = v;
    }
}
void dfs_top(int u, int fa)
{
    if (son[fa] == u)
        top[u] = top[fa];
    else
        top[u] = u;
    if (!son[u])
        return;
    dfs_top(son[u], u);
    for (int i = hd[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa || v == son[u])
            continue;
        dfs_top(v, u);
    }
}
int query(int u, int v)
{
    int cnt = 1;
    while (top[u] != top[v])
    {
        if (d[top[u]] < d[top[v]])
            v = p[top[v]];
        else
            u = p[top[u]];
        cnt++;
    }
    return cnt;
}
int main()
{
    freopen("pathdecomposition.in", "r", stdin);
    freopen("pathdecomposition.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        e[i] = {v, hd[u]};
        hd[u] = i;
        e[i + n - 1] = {u, hd[v]};
        hd[v] = i + n - 1;
    }
    dfs_son(1, 0);
    dfs_top(1, 0);
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        cout << query(x, y) << " ";
    }
    return 0;
}
