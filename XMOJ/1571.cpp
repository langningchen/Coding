#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 105;
struct EDGE
{
    ll to, Next;
} Edges[N * 2];
ll n, m, EdgeCount, b[N][N], f[N][N], Head[N];
bool Visited[N];
void AddEdge(ll u, ll v)
{
    EdgeCount++;
    Edges[EdgeCount].to = v;
    Edges[EdgeCount].Next = Head[u];
    Head[u] = EdgeCount;
}
void F(ll u)
{
    Visited[u] = true;
    for (ll i = Head[u]; i; i = Edges[i].Next)
    {
        ll v = Edges[i].to;
        if (Visited[v])
            continue;
        F(v);
        for (ll j = m; j > 0; j--)
            for (ll k = j - 1; k >= 0; k--)
                f[u][j] = max(f[u][j],
                              f[v][k] + f[u][j - k - 1] + b[u][v]);
    }
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i < n; i++)
    {
        ll x, y, z;
        scanf("%lld%lld%lld", &x, &y, &z);
        b[x][y] = b[y][x] = z;
        AddEdge(x, y);
        AddEdge(y, x);
    }
    F(1);
    printf("%lld\n", f[1][m]);
    return 0;
}
