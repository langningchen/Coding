#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
ll m, n, k, dis[N][N], f[N][N];
struct Edge
{
    ll from, to, val;
} e[N * N];
void Mul(ll d[N][N], ll a[N][N], ll b[N][N])
{
    ll t[N][N];
    memset(t, 0x3F, sizeof(t));
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= n; j++)
            for (ll k = 1; k <= n; k++)
                t[i][j] = min(t[i][j], a[i][k] + b[k][j]);
    memcpy(d, t, sizeof(t));
}
int main()
{
    // freopen("magic.in", "r", stdin);
    // freopen("magic.out", "w", stdout);
    cin >> n >> m >> k;
    memset(dis, 0x3F, sizeof(dis));
    for (ll i = 1; i <= m; i++)
    {
        cin >> e[i].from >> e[i].to >> e[i].val;
    }
    for (ll i = 1; i <= n; i++)
        dis[i][i] = 0;
    for (ll cc = 1; cc <= n; cc++)
        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][cc] + dis[cc][j]);
    memcpy(f, dis, sizeof(dis));
    for (ll i = 1; i <= m; i++)
    {
        ll u = e[i].from;
        ll v = e[i].to;
        ll w = e[i].val;
        for (ll j = 1; j <= n; j++)
        {
            for (ll cc = 1; cc <= n; cc++)
            {
                f[j][cc] = min(f[j][cc], dis[j][u] - w + dis[v][cc]);
            }
        }
    }
    for (; k; k >>= 1)
    {
        if (k & 1)
            Mul(dis, dis, f);
        Mul(f, f, f);
    }
    cout << f[1][n] << endl;
    return 0;
}