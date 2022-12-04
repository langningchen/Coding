#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
struct
{
    int to, nxt;
} e[N * 2];
int n, timer, sz[N], son[N], top[N], hd[N], dfn[N], id[N];
void dfs_son(int u, int fa)
{
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
    timer++;
    dfn[u] = timer;
    id[timer] = u;
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
int main()
{
    freopen("heavyfirst.in", "r", stdin);
    freopen("heavyfirst.out", "w", stdout);
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
    cout << id[1];
    for (int i = 2; i <= n; i++)
        cout << " " << id[i];
    cout << endl;
    cout << dfn[1];
    for (int i = 2; i <= n; i++)
        cout << " " << dfn[i];
    cout << endl;
    return 0;
}
