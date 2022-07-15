#include <bits/stdc++.h>
using namespace std;
const int N = 400005;
int n, m, to[N], hd[N], cnt[N], nxt[N], x[N], nE, tI[N], tO[N], id[N], clr[N], ans[N], timer;
struct Query
{
    int l, r, id, u, idB;
} q[N];
void addedge(int u, int v)
{
    to[++nE] = v;
    nxt[nE] = hd[u];
    hd[u] = nE;
}
void dfs(int u, int fa)
{
    tI[u] = ++timer;
    id[timer] = u;
    for (int i = hd[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa)
            continue;
        dfs(v, u);
    }
    tO[u] = timer;
}
void Input()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    for (int i = 1; i <= n; i++)
        cin >> clr[i];
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> q[i].u;
        q[i].id = i;
    }
}
bool cmp(const Query &a, const Query &b)
{
    if (a.idB < b.idB)
        return 1;
    if (a.idB > b.idB)
        return 0;
    if (a.idB & 1)
        return a.r < b.r;
    return a.r > b.r;
}
int main()
{
    Input();
    dfs(1, 0);
    int B = n / sqrt(2 * m) + 1;
    for (int i = 1; i <= m; i++)
    {
        int u = q[i].u;
        q[i].l = tI[u];
        q[i].r = tO[u];
        q[i].idB = (q[i].l - 1) / B + 1;
    }
    sort(q + 1, q + 1 + m, cmp);
    for (int i = 1; i <= n; i++)
    {
        x[i] = clr[id[i]];
    }
    int l = 0, r = 0, cUnq = 0;
    for (int i = 1; i <= m; i++)
    {
        while (l > q[i].l)
            cUnq += (++cnt[x[--l]] == 1);
        while (l < q[i].l)
            cUnq -= (--cnt[x[l++]] == 0);
        while (r < q[i].r)
            cUnq += (++cnt[x[++r]] == 1);
        while (r > q[i].r)
            cUnq -= (--cnt[x[r--]] == 0);
        ans[q[i].id] = cUnq;
    }
    for (int i = 1; i <= m; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
