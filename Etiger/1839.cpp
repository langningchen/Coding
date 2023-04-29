#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;
vector<int> to[N];
int L, n, m, q, p[N][20];
void dfs(int u, int fa)
{
    p[u][0] = fa;
    for (int i = 1; i <= L; i++)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = 0; i < to[u].size(); i++)
        if (to[u][i] != fa)
            dfs(to[u][i], u);
}
int LA(int u, int k)
{
    for (int i = 0; i <= L; i++)
        if ((1 << i) & k)
            u = p[u][i];
    return u;
}
int cnt[N], d[N], tI[N], tO[N], id[N], hd[N], nxt[N], son[N], ans[N];
void aNode(int u, bool tag)
{
    if (tag)
        cnt[d[u]]++;
    else
        cnt[d[u]]--;
}
void aTree(int u, bool tag)
{
    for (int i = tI[u]; i <= tO[u]; ++i)
        aNode(id[i], tag);
}
void dfs(int u, bool hvy)
{
    for (int i = hd[u]; i; i = nxt[i])
        if (son[u] != to[i])
            dfs(to[i], 0);
    if (son[u])
        dfs(son[u], 1);
    for (int i = hd[u]; i; i = nxt[i])
        if (to[i] != son[u])
            aTree(to[i], 1);
    aNode(u, 1);
    for (int i = 0; i < q[u].size(); i++)
        ans[q[u][i].id] = cnt[d[u] + q[u][i].k] - 1;
    if (hvy)
        return;
    aTree(u, 0);
}
int main()
{
    freopen("bro.in", "r", stdin);
    freopen("bro.out", "w", stdout);
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int v, k;
        cin >> v >> k;
        k = min(d[v] - 1, k);
        int u = LA(v, k);
        q[u].push_back((Query){i, k});
    }
    dfs(1, 0);
    dfs(1, 0);
    for (int i = 1; i <= m; i++)
        cout << ans[i] << endl;
    return 0;
}
