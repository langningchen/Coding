#include <bits/stdc++.h>
using namespace std;
const int N = 400005;
int n, m, k, to[N], hd[N], w[N], ccnt[N], cnt[N], nxt[N], x[N], nE, tI[N], tO[N], id[N], clr[N], ans[N], timer;
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
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> clr[i];
        w[i] = clr[i];
    }
    sort(w + 1, w + 1 + n);
    int nU = unique(w + 1, w + 1 + n) - w - 1;
    for (int i = 1; i <= n; i++)
    {
        clr[i] = lower_bound(w + 1, w + 1 + nU, clr[i]) - w;
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
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
    int l = 0, r = 0, val = 0;
    for (int i = 1; i <= m; i++)
    {
        while (l > q[i].l)
        {
            val = ++cnt[x[--l]];
            ccnt[val]++;
            ccnt[val - 1]--;
        }
        while (l < q[i].l)
        {
            val = --cnt[x[l++]];
            ccnt[val]++;
            ccnt[val + 1]--;
        }
        while (r < q[i].r)
        {
            val = ++cnt[x[++r]];
            ccnt[val]++;
            ccnt[val - 1]--;
        }
        while (r > q[i].r)
        {
            val = --cnt[x[r--]];
            ccnt[val]++;
            ccnt[val + 1]--;
        }
        ans[q[i].id] = ccnt[k];
    }
    for (int i = 1; i <= m; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
