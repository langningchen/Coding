#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 40009;
const ll M = 100009;
struct EDGE
{
    ll a, b, c;
} Edges[M];
ll n, m, id[N];
ll find(ll x) { return id[x] == x ? x : id[x] = find(id[x]); }
void unite(ll x, ll y) { id[find(x)] = find(y); }
bool cmp(const EDGE &x, const EDGE &y) { return x.c > y.c; }
int main()
{
    freopen("prison.in", "r", stdin);
    freopen("prison.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%lld%lld%lld", &Edges[i].a, &Edges[i].b, &Edges[i].c);
    sort(Edges, Edges + m, cmp);
    for (int i = 1; i <= n + n; i++)
        id[i] = i;
    ll ans = 0;
    for (int i = 0; i < m; i++)
    {
        ll fa = find(Edges[i].a), fb = find(Edges[i].b);
        if (fa == fb)
        {
            ans = Edges[i].c;
            break;
        }
        unite(Edges[i].a, Edges[i].b + n);
        unite(Edges[i].b, Edges[i].a + n);
    }
    printf("%lld\n", ans);
    return 0;
}
