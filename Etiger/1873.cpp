#include <bits/stdc++.h>
using namespace std;
const int N = 100'005;
int n, hd[N], nxt[N << 1], to[N << 1], tot;
int son[N], sz[N], dep[N], fa[N], id[N], tI[N], tO[N], t;
int path[N], cnt[N], res;
long long ans[N];
void addEdge(int u, int v)
{
    nxt[++tot] = hd[u];
    hd[u] = tot;
    to[tot] = v;
}
void dfs_son(int u, int fa)
{
    sz[u] = 1;
    for (int i = hd[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa)
            continue;
        dep[v] = dep[u] + 1;
        dfs_son(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]])
            son[u] = v;
    }
}
void dfs_path(int u, int fa)
{
    for (int i = hd[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa)
            continue;
        path[v] = path[u] ^ v;
        dfs_path(v, u);
    }
}
void dfs_tIO(int u, int fa)
{
    tI[u] = ++t;
    if (son[u])
    {
        dfs_tIO(son[u], u);
    }
    for (int i = hd[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa || v == son[u])
            continue;
        dfs_tIO(v, u);
    }
    tO[u] = t;
}
void useNode(int v, int lca)
{
    res += cnt[path[v] ^ lca];
}
void useTree(int v, int lca)
{
    for (int i = tI[v]; i <= tO[v]; i++)
        useNode(id[i], lca);
}
void addNode(int u, bool ADD)
{
    if (ADD)
        cnt[path[u]]++;
    else
        cnt[path[u]]--;
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
    res = 0;
    for (int i = hd[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == son[u] || v == fa)
            continue;
        useTree(v, u);
        addTree(v, 1);
    }
    useNode(u, u);
    addNode(u, 1);
    ans[u] = res;
    if (hvy)
        return;
    addTree(u, 0);
}
int main()
{
    // freopen("xor3.in", "r", stdin);
    // freopen("xor3.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs_son(1, 0);
    dfs_tIO(1, 0);
    for (int i = 1; i <= n; i++)
        id[tI[i]] = i;
    path[1] = 1;
    dfs_path(1, 0);
    dfs(1, 0, 0);
    int Ans = 0;
    for (int i = 1; i <= n; i++)
    {
        Ans += (ans[i] == 0);
        cout << ans[i] << " ";
    }
    printf("%d\n", Ans);
    return 0;
}
