#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll T, n, q, Father[N], x[N], y[N];
struct EDGE
{
    ll u, v;
    ll w;
} Edges[N * N];
vector<pair<ll, vector<ll>>> Networks;
ll EdgeCount = 0;
ll Find(ll x)
{
    return (x == Father[x] ? Father[x] : Father[x] = Find(Father[x]));
}
void Union(ll x, ll y)
{
    Father[Find(x)] = Find(y);
}
void AddEdge(ll u, ll v, ll w)
{
    Edges[EdgeCount].u = u;
    Edges[EdgeCount].v = v;
    Edges[EdgeCount].w = w;
    EdgeCount++;
    Edges[EdgeCount].u = v;
    Edges[EdgeCount].v = u;
    Edges[EdgeCount].w = w;
    EdgeCount++;
}
ll Kruskal()
{
    ll Answer = 0;
    for (ll i = 0; i < EdgeCount; i++)
        if (Find(Edges[i].u) != Find(Edges[i].v))
        {
            Union(Edges[i].u, Edges[i].v);
            Answer += Edges[i].w;
        }
    return Answer;
}
ll Visited[N], Distance[N];
ll Prim()
{
    memset(Visited, 0, sizeof(Visited));
    memset(Distance, 0x7f, sizeof(Distance));
    Distance[1] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    q.push(make_pair(0, 1));
    ll Answer = 0;
    while (!q.empty())
    {
        pair<ll, ll> t = q.top();
        q.pop();
        ll u = t.second;
        if (Visited[u])
            continue;
        Visited[u] = 1;
        Answer += t.first;
        for (ll i = 0; i < EdgeCount; i++)
            if (Edges[i].u == u && Distance[Edges[i].v] > Edges[i].w && !Visited[Edges[i].v])
            {
                Distance[Edges[i].v] = Edges[i].w;
                q.push(make_pair(Distance[Edges[i].v], Edges[i].v));
            }
    }
    return Answer;
}
void Input()
{
    scanf("%lld%lld", &n, &q);
    for (ll i = 1; i <= q; i++)
    {
        ll m, c;
        scanf("%lld%lld", &m, &c);
        vector<ll> Temp;
        for (ll j = 1; j <= m; j++)
        {
            ll t;
            scanf("%lld", &t);
            Temp.push_back(t);
        }
        Networks.push_back(make_pair(c, Temp));
    }
    for (ll i = 1; i <= n; i++)
        scanf("%lld%lld", &x[i], &y[i]);
    for (ll i = 1; i <= n; i++)
        for (ll j = i + 1; j <= n; j++)
            AddEdge(i, j, (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
    sort(Edges, Edges + EdgeCount,
         [](EDGE a, EDGE b)
         {
             return a.w < b.w;
         });
}
ll Solve(ll Status)
{
    for (ll i = 1; i <= n; i++)
        Father[i] = i;
    EdgeCount = n * (n - 1);
    ll Answer = 0;
    for (size_t i = 0; i < Networks.size(); i++)
        if (Status & (1 << i))
        {
            Answer += Networks[i].first;
            for (size_t j = 0; j < Networks[i].second.size(); j++)
                for (size_t k = j + 1; k < Networks[i].second.size(); k++)
                    Union(Networks[i].second[j], Networks[i].second[k]);
        }
    Answer += Kruskal();
    return Answer;
}
int main()
{
    scanf("%lld", &T);
    while (T-- > 0)
    {
        EdgeCount = 0;
        Networks.clear();
        Input();
        ll Answer = INF;
        for (ll i = 0; i < (1 << q); i++)
            Answer = min(Answer, Solve(i));
        printf("%lld\n", Answer);
    }
    return 0;
}
