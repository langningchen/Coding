#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
const int MOD = 100000007;
struct node
{
    int nxt, to;
} e[N * 2];
int n, m, timer, nE, hd[N], d[N], p[N], sz[N], son[N], tI[N], tO[N], top[N], bit[N];
void add_edge(int u, int v)
{
    e[++nE].to = v;
    e[nE].nxt = hd[u];
    hd[u] = nE;
}
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
        if (sz[son[u]] < sz[v])
            son[u] = v;
    }
}
void dfs_top_tIO(int u, int fa)
{
    tI[u] = ++timer;
    tO[u] = tI[u] + sz[u] - 1;
    if (son[fa] == u)
        top[u] = top[fa];
    else
        top[u] = u;
    if (!son[u])
        return;
    dfs_top_tIO(son[u], u);
    for (int i = hd[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa || v == son[u])
            continue;
        dfs_top_tIO(v, u);
    }
}
int LSB(int x)
{
    return x & (-x);
}
void add(int i, int w)
{
    while (i <= n)
    {
        bit[i] += w;
        bit[i] %= MOD;
        i += LSB(i);
    }
}
int psq(int i)
{
    int sum = 0;
    while (i)
    {
        sum = (sum + bit[i]) % MOD;
        i -= LSB(i);
    }
    return sum;
}
int rsq(int l, int r)
{
    int res = psq(r) - psq(l - 1);
    return (res % MOD + MOD) % MOD;
}
int query(int x)
{
    int ans = 0;
    while (x)
    {
        ans += rsq(tI[top[x]], tI[x]);
        ans %= MOD;
        x = p[top[x]];
    }
    return ans;
}
int main()
{
    freopen("company.in", "r", stdin);
    freopen("company.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs_son(1, 0);
    dfs_top_tIO(1, 0);
    for (int i = 1; i <= m; i++)
    {
        int x, w;
        cin >> x >> w;
        add(tI[x], w);
        cout << query(x) << endl;
    }
    return 0;
}
