#include <bits/stdc++.h>
using namespace std;
const int N = 100'005;
int n, res, timer, tot, sz[N], nxt[N << 1], hd[N], to[N << 1], tI[N], tO[N], clr[N], cnt[N], cntAll[N], id[N], son[N], ans[N];
void dfs_son(int u, int fa = 0)
{
    sz[u] = 1;
    son[u] = 0;
    for (int i = hd[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa)
            continue;
        dfs_son(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v])
            son[u] = v;
    }
}
void dfs_tIO(int u, int fa = 0)
{
    tI[u] = ++timer;
    tO[u] = tI[u] + sz[u] - 1;
    if (!son[u])
        return;
    dfs_tIO(son[u], u);
    for (int i = hd[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa || v == son[u])
            continue;
        dfs_tIO(v, u);
    }
}
void addEdge(int u, int v)
{
    nxt[++tot] = hd[u];
    hd[u] = tot;
    to[tot] = v;
}
void addNode(int u, bool ADD)
{
    int &c = clr[u];
    if (ADD)
    {
        cnt[c]++;
        if (cnt[c] == 1)
            res++;
        if (cnt[c] == cntAll[c])
            res--;
    }
    else
        cnt[c]--;
}
void addTree(int u, bool ADD)
{
    for (int i = tI[u]; i <= tO[u]; i++)
        addNode(id[i], ADD);
}
void dfs(int u, int fa, bool hvy)
{
    for (int i = hd[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == son[u] || v == fa)
            continue;
        dfs(v, u, 0);
    }
    if (son[u])
        dfs(son[u], u, 1);
    for (int i = hd[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == son[u] || v == fa)
            continue;
        addTree(v, 1);
    }
    addNode(u, 1);
    ans[u] = res;
    if (hvy)
        return;
    addTree(u, 0);
    res = 0;
}
int main()
{
    freopen("ctree.in", "r", stdin);
    freopen("ctree.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &clr[i]);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs_son(1);
    dfs_tIO(1);
    for (int i = 1; i <= n; i++)
        id[tI[i]] = i;
    for (int i = 1; i <= n; i++)
        cntAll[clr[i]]++;
    dfs(1, 0, 0);
    for (int i = 2; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}
