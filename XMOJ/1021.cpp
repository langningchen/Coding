#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 10005;
const ll M = 1000005;
const ll INF = 0x3FFF'FFFF'FFFF'FFFF;
ll n, m, s, t;
struct EDGE
{
    ll to, next, w;
} Edges[M << 1];
ll EdgeCount, Head[N];
void AddEdge(ll u, ll v, ll w)
{
    Edges[++EdgeCount].to = v;
    Edges[EdgeCount].next = Head[u];
    Edges[EdgeCount].w = w;
    Head[u] = EdgeCount;
}
ll Distance[N];
void Dijkstra()
{
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    for (ll i = 1; i <= n; i++)
        Distance[i] = INF;
    Distance[s] = 0;
    q.push({0, s});
    while (!q.empty())
    {
        ll u = q.top().second;
        q.pop();
        for (ll i = Head[u]; i; i = Edges[i].next)
        {
            ll v = Edges[i].to;
            if (Distance[v] > Distance[u] + Edges[i].w)
            {
                Distance[v] = Distance[u] + Edges[i].w;
                q.push({Distance[v], v});
            }
        }
    }
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= m; i++)
    {
        ll u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        AddEdge(u, v, w);
        AddEdge(v, u, w);
    }
    scanf("%lld%lld", &s, &t);
    Dijkstra();
    printf("%lld\n", (Distance[t] == INF) ? -1 : Distance[t]);
    return 0;
}
