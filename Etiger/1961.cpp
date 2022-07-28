#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
ll n, q, L;
ll d[N], p[N][105], t[N];
ll timer, tI[N], tO[N];
struct edge
{
    ll to, nxt, w;
} e[N * 2];
ll nE, hd[N];
void addE(ll u, ll v, ll w)
{
    e[++nE].to = v;
    e[nE].nxt = hd[u];
    e[nE].w = w;
    hd[u] = nE;
    e[++nE].to = u;
    e[nE].nxt = hd[v];
    e[nE].w = w;
    hd[v] = nE;
}
void dfs(ll u, ll fa)
{
    tI[u] = ++timer;
    p[u][0] = fa;
    for (ll i = 1; i <= L; i++)
    {
        p[u][i] = p[p[u][i - 1]][i - 1];
    }
    for (ll i = hd[u]; i; i = e[i].nxt)
    {
        ll v = e[i].to;
        if (v == fa)
            continue;
        d[v] = d[u] + e[i].w;
        dfs(v, u);
    }
    tO[u] = timer;
}
bool up(ll u, ll v)
{
    return !u || tI[u] <= tI[v] && tO[v] <= tO[u];
}
ll lca(ll u, ll v)
{
    if (up(u, v))
        return u;
    if (up(v, u))
        return v;
    for (ll i = L; i >= 0; i--)
    {
        if (!up(p[u][i], v))
        {
            u = p[u][i];
        }
    }
    return p[u][0];
}
ll dst(ll u, ll v)
{
    return d[u] + d[v] - 2 * d[lca(u, v)];
}
int main()
{
    freopen("visit.in", "r", stdin);
    freopen("visit.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        addE(u, v, w);
    }
    L = log(n) / log(2) + 1;
    d[1] = 1;
    timer = 0;
    memset(p, 0, sizeof(p));
    dfs(1, 0);

    ll B = max_element(d + 1, d + 1 + n) - d;
    d[B] = 1;
    timer = 0;
    dfs(B, 0);

    ll C = max_element(d + 1, d + 1 + n) - d;
    d[C] = 1;
    timer = 0;
    dfs(1, 0);

    ll ans = 0;
    for (ll A = 1; A <= n; A++)
    {
        ll AB = dst(A, B);
        ll AC = dst(A, C);
        ll cost = min(AB, AC) + dst(B, C);
        ans = max(ans, cost);
    }
    cout << ans << endl;
    return 0;
}
