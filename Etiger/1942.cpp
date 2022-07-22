#include <bits/stdc++.h>
using namespace std;
const int N = 500005;
struct Edge
{
    int v, w, nxt;
} e[N * 2];
struct Query
{
    int t, u, v;
} q[N];
int timer, nE, n, nQ, hd[N], x, y, w, L, tI[N], tO[N], d[N], id[N], p[N][20], vst[N];
void add(int u, int v, int w)
{
    e[++nE] = (Edge){v, w, hd[u]};
    hd[u] = nE;
}
bool up(int u, int v)
{
    return !u || tI[u] <= tI[v] && tO[v] <= tO[u];
}
int lca(int u, int v)
{
    if (up(u, v))
        return u;
    if (up(v, u))
        return v;
    for (int i = L; i >= 0; i--)
        if (!up(p[u][i], v))
            u = p[u][i];
    return p[u][0];
}
int dst(int u, int v)
{
    return d[u] + d[v] - 2 * d[lca(u, v)];
}
int root(int u)
{
    return id[u] == u ? u : id[u] = root(id[u]);
}
int input()
{
    freopen("treelink.in", "r", stdin);
    freopen("treelink.out", "w", stdout);
    cin >> n >> nQ;
    for (int i = 1; i <= nQ; i++)
    {
        scanf("%d %d", &x, &y);
        char ch = getchar();
        if (ch != ' ')
        {
            q[i] = (Query){2, x, y};
            continue;
        }
        scanf("%d", &w);
        add(x, y, w);
        add(y, x, w);
        q[i] = (Query){3, x, y};
    }
    return 0;
}
void dfs(int u, int fa)
{
    vst[u] = 1;
    tI[u] = ++timer;
    p[u][0] = fa;
    for (int i = 1; i < L; i++)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = hd[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == fa)
            continue;
        d[v] = d[u] + e[i].w;
        dfs(v, u);
    }
    tO[u] = ++timer;
}
int main()
{
    input();
    L = log2(n) + 1;
    for (int u = 1; u <= n; u++)
        if (!vst[u])
            dfs(u, 0);
    for (int u = 1; u <= n; u++)
        id[u] = u;
    for (int i = 1; i <= nQ; i++)
    {
        int u = q[i].u;
        int v = q[i].v;
        int ru = root(u);
        int rv = root(v);
        if (q[i].t == 3)
        {
            id[ru] = rv;
            continue;
        }
        if (ru != rv)
            cout << -1 << endl;
        else
            cout << dst(u, v) << endl;
    }
    return 0;
}