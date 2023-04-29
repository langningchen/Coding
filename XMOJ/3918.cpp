#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll n, k, l, fa[N];
map<ll, map<ll, bool>> CanVisit;
ll find(ll x)
{
    return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}
void merge(ll x, ll y)
{
    x = find(x);
    y = find(y);
    if (x != y)
        fa[x] = y;
}
int main()
{
    // freopen("d.in", "r", stdin);
    // freopen("d.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &k, &l);
    for (ll i = 1; i <= n; i++)
        fa[i] = i;
    for (ll i = 1; i <= k; i++)
    {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        merge(x, y);
    }
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= n; j++)
            CanVisit[i][j] = (find(i) == find(j));
    for (ll i = 1; i <= n; i++)
        fa[i] = i;
    for (ll i = 1; i <= l; i++)
    {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        merge(x, y);
    }
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= n; j++)
            CanVisit[i][j] = CanVisit[i][j] && (find(i) == find(j));
    for (ll i = 1; i <= n; i++)
    {
        ll Answer = 0;
        for (ll j = 1; j <= n; j++)
            if (CanVisit[i][j])
                Answer++;
        printf("%lld ", Answer);
    }
    return 0;
}
