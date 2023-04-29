#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll n, m;
struct REQUEST
{
    ll a, b;
} Request[N];
int main()
{
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= m; i++)
        scanf("%lld%lld", &Request[i].a, &Request[i].b);
    sort(Request + 1, Request + m + 1,
         [](REQUEST a, REQUEST b)
         {
             if (a.b == b.b)
                 return a.a < b.a;
             return a.b < b.b;
         });
    ll Answer = 0;
    ll Current = 0;
    for (ll i = 1; i <= m; i++)
        if (Request[i].a >= Current)
        {
            Answer++;
            Current = Request[i].b;
        }
    printf("%lld\n", Answer);
    return 0;
}
