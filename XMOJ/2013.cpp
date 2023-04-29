#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 55;
const ll M = 2005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll n, m, P[N], Cost[N], Limit[N], Temp[M], h[M], f[N][105][M], g[M];
struct EDGE
{
    ll u, v, w, next;
} Edge[N * N];
ll Counter = 1, Head[N], in[N];
void AddEdge(ll u, ll v, ll w)
{
    Counter++;
    Edge[Counter] = {u, v, w, Head[u]};
    Head[u] = Counter;
    in[v]++;
}
void F(ll u)
{
    if (!Head[u])
    {
        Limit[u] = min(Limit[u], m / Cost[u]);
        for (ll i = 0; i <= Limit[u]; i++)
            for (ll j = i; j <= Limit[u]; j++)
                f[u][i][j * Cost[u]] = (j - i) * P[u];
        return;
    }
    Limit[u] = INF;
    ll i = Head[u];
    while (i)
    {
        ll v = Edge[i].v;
        F(v);
        Limit[u] = min(Limit[u], Limit[v] / Edge[i].w);
        Cost[u] += Edge[i].w * Cost[v];
        i = Edge[i].next;
    }
    Limit[u] = min(Limit[u], m / Cost[u]);
    for (ll l = 0; l <= Limit[u]; l++)
    {
        for (ll i = 0; i <= m; i++)
            g[i] = -INF;
        g[0] = 0;
        ll i = Head[u];
        while (i)
        {
            memcpy(Temp, g, sizeof(g));
            for (ll j = 0; j <= m; j++)
                g[j] = -INF;
            for (ll j = 0; j <= m; j++)
                for (ll k = 0; Temp[j] >= 0 && j + k <= m; k++)
                    g[j + k] = max(g[j + k], Temp[j] + f[Edge[i].v][l * Edge[i].w][k]);
            i = Edge[i].next;
        }
        for (ll j = 0; j <= l; j++)
            for (ll k = 0; k <= m; k++)
                f[u][j][k] = max(f[u][j][k], g[k] + (l - j) * P[u]);
    }
}
int main()
{
    scanf("%lld %lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        char Type = 0;
        scanf("%lld %c", &P[i], &Type);
        if (Type == 'A')
        {
            ll C = 0;
            scanf("%lld", &C);
            for (ll j = 1; j <= C; j++)
            {
                ll v = 0, w = 0;
                scanf("%lld %lld", &v, &w);
                AddEdge(i, v, w);
            }
        }
        else
            scanf("%lld %lld", &Cost[i], &Limit[i]);
    }
    for (ll i = 0; i < N; i++)
        for (ll j = 0; j < 105; j++)
            for (ll k = 0; k < M; k++)
                f[i][j][k] = -INF;
    for (ll u = 1; u <= n; u++)
        if (!in[u])
        {
            F(u);
            memcpy(Temp, h, sizeof(h));
            memset(h, 0, sizeof(h));
            for (ll i = 0; i <= m; i++)
                for (ll j = i; j <= m; j++)
                    h[j] = max(h[j], Temp[i] + f[u][0][j - i]);
        }
    ll Answer = -INF;
    for (ll i = 0; i <= m; i++)
        Answer = max(Answer, h[i]);
    printf("%lld\n", Answer);
    return 0;
}
