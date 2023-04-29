#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll n, t, ans = INF;
int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%lld%lld", &n, &t);
    for (ll i = 1; i <= n; i++)
    {
        ll c, _t;
        scanf("%lld%lld", &c, &_t);
        if (_t <= t)
            ans = min(ans, c);
    }
    if (ans == INF)
        printf("TLE\n");
    else
        printf("%lld\n", ans);
    return 0;
}