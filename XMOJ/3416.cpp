#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const int MAXN = 60005;
const int MAXLOG = 20;
int n, q, hd[MAXN], sons[MAXN], to[MAXN * 2], nxt[MAXN * 2], tot, dep[MAXN], anc[MAXN][MAXLOG];
void link(int father, int son)
{
    ++tot;
    to[tot] = son;
    nxt[tot] = hd[father];
    hd[father] = tot;
}
void dfs(int x, int f)
{
    dep[x] = dep[f] + 1;
    anc[x][0] = f;
    for (int i = 1; i < MAXLOG; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (int i = hd[x]; i; i = nxt[i])
        if (to[i] != f)
            dfs(to[i], x);
}
int lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (dep[anc[x][i]] >= dep[y])
            x = anc[x][i];
    if (x == y)
        return x;
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (anc[x][i] != anc[y][i])
            x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        link(x, y);
        link(y, x);
    }
    dfs(1, 0);
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", lca(x, y));
    }
    return 0;
}
