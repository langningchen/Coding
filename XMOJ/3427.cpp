#include <bits/stdc++.h>
const int N = 60005;
int n, tot, hd[N], to[N * 2], w[N * 2], nxt[N * 2], x, y, dis[N], len;
void dfs(int u, int fa, int l)
{
    dis[u] = dis[fa] + l;
    for (int i = hd[u]; i; i = nxt[i])
        if (to[i] != fa)
            dfs(to[i], u, w[i]);
}
void work()
{
    dfs(1, 0, 0);
    x = 1;
    for (int i = 2; i <= n; ++i)
        if (dis[i] > dis[x])
            x = i;
    dfs(x, 0, 0);
    y = 1;
    for (int i = 2; i <= n; ++i)
        if (dis[i] > dis[y])
            y = i;
    len = dis[y];
}
void AddEdge(int x, int y, int z)
{
    to[++tot] = y;
    nxt[tot] = hd[x];
    hd[x] = tot;
    w[tot] = z;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        AddEdge(x, y, z);
        AddEdge(y, x, z);
    }
    work();
    printf("%d\n", len);
    return 0;
}
