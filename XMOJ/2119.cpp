#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 205;
struct EDGE
{
    ll to, Value, Next;
} Edges[N * N];
ll m, n, t, c[N], u[N], Head[N];
bool InputLayer[N], OutputLayer[N], Visited[N];
ll EdgeCounter = 0;
void AddEdge(ll u, ll v, ll w)
{
    EdgeCounter++;
    Edges[EdgeCounter].to = v;
    Edges[EdgeCounter].Value = w;
    Edges[EdgeCounter].Next = Head[u];
    Head[u] = EdgeCounter;
}
void TopoSort()
{
    queue<ll> q;
    for (ll i = 1; i <= n; i++)
        if (InputLayer[i])
        {
            q.push(i);
            Visited[i] = true;
        }
    while (!q.empty())
    {
        ll h = q.front();
        q.pop();
        if (c[h] <= 0)
            continue;
        for (ll i = Head[h]; i; i = Edges[i].Next)
        {
            t = Edges[i].to;
            c[t] += Edges[i].Value * c[h];
            if (!Visited[t])
            {
                q.push(t);
                Visited[t] = true;
            }
        }
    }
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &c[i], &u[i]);
        if (c[i] == 0)
            c[i] -= u[i];
        else
            InputLayer[i] = true;
    }
    fill(OutputLayer + 1, OutputLayer + n + 1, true);
    for (ll i = 1; i <= m; i++)
    {
        ll u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        AddEdge(u, v, w);
        OutputLayer[u] = false;
    }
    TopoSort();
    bool FoundAnswer = false;
    for (ll i = 1; i <= n; i++)
        if (OutputLayer[i] && c[i] > 0)
        {
            printf("%lld %lld\n", i, c[i]);
            FoundAnswer = true;
        }
    if (!FoundAnswer)
        printf("NULL\n");
    return 0;
}
