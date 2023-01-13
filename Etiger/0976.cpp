#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int MOD = 100000007;
struct node
{
    int nxt, to;
} e[N * 2];
ll n, m, timer, nE, hd[N], d[N], p[N], sz[N], son[N], tI[N], tO[N], top[N], bit[N], a[N], b[N], c[N], bs[N], x[N], B;
void add_edge(int u, int v)
{
    e[++nE].to = v;
    e[nE].nxt = hd[u];
    hd[u] = nE;
}
void dfs_son(int u, int fa = 0)
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
void dfs_top_tIO(int u, int fa = 0)
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
void add(ll l, ll r, ll z)
{
    if (b[l] == b[r])
    {
        for (ll i = l; i <= r; i++)
        {
            a[i] = (a[i] + z) % MOD;
            bs[b[i]] = (bs[b[i]] + z) % MOD;
        }
        return;
    }
    for (ll i = l; b[i] == b[l]; i++)
    {
        a[i] = (a[i] + z) % MOD;
        bs[b[i]] = (bs[b[i]] + z) % MOD;
    }
    for (ll i = r; b[i] == b[r]; i--)
    {
        a[i] = (a[i] + z) % MOD;
        bs[b[i]] = (bs[b[i]] + z) % MOD;
    }
    for (ll iB = b[l] + 1; iB <= b[r] - 1; iB++)
    {
        c[iB] = (c[iB] + z) % MOD;
        bs[iB] = (bs[iB] + z * B) % MOD;
    }
}
ll rsq(ll l, ll r)
{
    ll ans = 0;
    if (b[l] == b[r])
    {
        for (ll i = l; i <= r; i++)
            ans = (ans + a[i] + c[b[i]]) % MOD;
        return ans;
    }
    for (ll i = l; b[i] == b[l]; i++)
        ans = (ans + a[i] + c[b[i]]) % MOD;
    for (ll i = r; b[i] == b[r]; i--)
        ans = (ans + a[i] + c[b[i]]) % MOD;
    for (ll iB = b[l] + 1; iB <= b[r] - 1; iB++)
        ans = (ans + bs[iB] + c[iB] * B) % MOD;
    return ans;
}
void solve(ll u, ll v, ll w)
{
    ll ans = 0;
    while (top[u] != top[v])
    {
        ll &x = (d[top[u]] > d[top[v]] ? u : v);
        ans += rsq(tI[top[x]], tI[x]);
        ans %= MOD;
        add(tI[top[x]], tI[x], w);
        x = p[top[x]];
    }
    if (d[u] > d[v])
        swap(u, v);
    ans += rsq(tI[u], tI[v]);
    ans %= MOD;
    add(tI[u], tI[v], w);
    cout << ans << endl;
}
int main()
{
    freopen("company3.in", "r", stdin);
    freopen("company3.out", "w", stdout);
    cin >> n >> m;
    for (ll u = 1; u <= n; u++)
        cin >> x[u];
    for (ll i = 1; i <= n - 1; i++)
    {
        ll u, v;
        cin >> u >> v;
        add_edge(u, v);
        p[v] = u;
    }
    dfs_son(1);
    dfs_top_tIO(1);
    for (ll u = 1; u <= n; u++)
        a[tI[u]] = x[u];
    B = sqrt(n) + 1;
    for (ll i = 1; i <= n; i++)
        b[i] = (i - 1) / B + 1;
    for (ll i = 1; i <= n; i++)
        bs[b[i]] = (bs[b[i]] + a[i]) % MOD;
    for (ll i = 1; i <= m; i++)
    {

        ll u, v, w;
        cin >> u >> v >> w;
        solve(u, v, w);
    }
    return 0;
}