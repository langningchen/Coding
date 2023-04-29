#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 6010;
struct EDGE
{
    ll u, v, Next;
} Edges[N];
ll n, Head[N], EdgeCount, w[N], Root, f[N][2];
bool Visit[N];
void AddEdge(ll u, ll v)
{
    EdgeCount++;
    Edges[EdgeCount].u = u;
    Edges[EdgeCount].v = v;
    Edges[EdgeCount].Next = Head[u];
    Head[u] = EdgeCount;
}
void F(ll u, ll fa)
{
    f[u][0] = 0;
    f[u][1] = w[u];
    for (ll i = Head[u]; i; i = Edges[i].Next)
    {
        ll v = Edges[i].v;
        if (v != fa)
        {
            F(v, u);
            f[u][0] += max(f[v][0], f[v][1]);
            f[u][1] += f[v][0];
        }
    }
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &w[i]);
    for (ll i = 1; i < n; i++)
    {
        ll u, v;
        scanf("%lld%lld", &v, &u);
        AddEdge(u, v);
        Visit[v] = true;
    }
    for (ll i = 1; i <= n; ++i)
        if (!Visit[i])
        {
            Root = i;
            break;
        }
    F(Root, 0);
    printf("%lld\n", max(f[Root][0], f[Root][1]));
    return 0;
}
