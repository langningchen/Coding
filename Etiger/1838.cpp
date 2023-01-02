#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100009;
struct query
{
    int id, k;
};
int n, m, timer, nE,
    sz[N], tI[N], tO[N], id[N], son[N],
    p[N], d[N], iName[N], ans[N],
    to[N * 2], hd[N * 2], nxt[N * 2];
set<int> S[N * 2];
vector<query> q[N];
void addedge(ll u, ll v)
{
    to[++nE] = v;
    nxt[nE] = hd[u];
    hd[u] = nE;
}
void dfs_pre(ll u, ll fa = 0)
{
    sz[u] = 1;
    son[u] = 0;
    timer++;
    tI[u] = timer;
    id[timer] = u;
    for (ll i = hd[u]; i; i = nxt[i])
    {
        ll v = to[i];
        if (v == fa)
            continue;
        d[v] = d[u] + 1;
        dfs_pre(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v])
            son[u] = v;
    }
    tO[u] = timer;
}
void aNode(int u, bool tag)
{
    if (tag)
        S[d[u]].insert(iName[u]);
    else
        S[d[u]].erase(iName[u]);
}
void aTree(int u, bool tag)
{
    for (int i = tI[u]; i <= tO[u]; i++)
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
        if (son[u] != to[i])
            aTree(to[i], 1);
    aNode(u, 1);
    for (size_t i = 0; i < q[u].size(); i++)
        ans[q[u][i].id] = S[d[u] + q[u][i].k].size();
    if (hvy)
        return;
    aTree(u, 0);
}
void input()
{
    map<string, int> names;
    int nNames = 0;
    cin >> n;
    for (int u = 1; u <= n; u++)
    {
        string s;
        cin >> s;
        if (names.count(s))
            iName[u] = names[s];
        else
            iName[u] = names[s] = ++nNames;
        cin >> p[u];
        if (p[u])
            addedge(p[u], u);
    }
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int v, k;
        cin >> v >> k;
        q[v].push_back((query){i, k});
    }
}
void solve()
{
    for (int u = 1; u <= n; u++)
        if (!p[u])
            dfs_pre(u);
    for (int u = 1; u <= n; u++)
        if (!p[u])
            dfs(u, 0);
    for (int i = 1; i < m; i++)
        cout << ans[i] << " ";
    cout << ans[m] << endl;
}
int main()
{
    freopen("offspring.in", "r", stdin);
    freopen("offspring.out", "w", stdout);
    input();
    solve();
    return 0;
}
