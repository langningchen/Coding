#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1505;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
struct EDGE
{
    ll to, Next;
} Edges[2 * N];
ll EdgeCount, n, k[N], Head[N], f[N][3];
bool Visit[N];
void add(ll x, ll y)
{
    Edges[++EdgeCount].to = y;
    Edges[EdgeCount].Next = Head[x];
    Head[x] = EdgeCount;
}
void F(ll u)
{
    for (ll i = Head[u]; i; i = Edges[i].Next)
    {
        F(Edges[i].to);
        f[u][2] += f[Edges[i].to][1];
        f[u][0] += min(f[Edges[i].to][0], min(f[Edges[i].to][1], f[Edges[i].to][2]));
    }
    f[u][0] += k[u];
    ll Temp[N] = {0};
    memset(Temp, 0, sizeof(Temp));
    ll Temp2 = 0;
    for (ll i = Head[u]; i; i = Edges[i].Next)
    {
        Temp[Edges[i].to] = min(f[Edges[i].to][0], f[Edges[i].to][1]);
        Temp2 += Temp[Edges[i].to];
    }
    f[u][1] = INF;
    for (ll i = Head[u]; i; i = Edges[i].Next)
        if (Temp2 - Temp[Edges[i].to] + f[Edges[i].to][0] < f[u][1])
            f[u][1] = Temp2 - Temp[Edges[i].to] + f[Edges[i].to][0];
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        ll x, m;
        scanf("%lld", &x);
        scanf("%lld%lld", &k[x], &m);
        for (ll j = 1; j <= m; j++)
        {
            ll y;
            scanf("%lld", &y);
            add(x, y);
            Visit[y] = true;
        }
    }
    for (ll i = 1; i <= n; i++)
        if (!Visit[i])
        {
            F(i);
            printf("%lld\n", min(f[i][0], f[i][1]));
            break;
        }
    return 0;
}
