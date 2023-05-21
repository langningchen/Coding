#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 105;
ll n;
struct EDGE
{
    ll to, next, w;
} Edges[N * N];
ll EdgeCount, Head[N];
void AddEdge(ll u, ll v, ll w)
{
    Edges[++EdgeCount].to = v;
    Edges[EdgeCount].next = Head[u];
    Edges[EdgeCount].w = w;
    Head[u] = EdgeCount;
}
bool Visited[N];
ll Kruskal()
{
    ll Answer = 0;
    ll ChosenEdgeCount = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> Queue;
    Queue.push({0, 1});
    while (!Queue.empty())
    {
        ll u = Queue.top().second;
        ll w = Queue.top().first;
        Queue.pop();
        if (Visited[u])
            continue;
        Visited[u] = true;
        Answer += w;
        ChosenEdgeCount++;
        if (ChosenEdgeCount == n)
            break;
        for (ll i = Head[u]; i; i = Edges[i].next)
        {
            ll v = Edges[i].to;
            if (!Visited[v])
                Queue.push({Edges[i].w, v});
        }
    }
    return Answer;
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n * (n - 1) / 2; i++)
    {
        ll u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        AddEdge(u, v, w);
        AddEdge(v, u, w);
    }
    printf("%lld\n", Kruskal());
    return 0;
}
