#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll n, w[N], a[N], b[N], ans;
int main()
{
    freopen("exchange.in", "r", stdin);
    freopen("exchange.out", "w", stdout);
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &w[i]);
        ans += w[i];
    }
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &b[i]);
    printf("%lld\n", ans);
    return 0;
}
