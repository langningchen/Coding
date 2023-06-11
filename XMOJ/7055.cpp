#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll N = 100010;
ll n, t, c[N], h[N];
ld w[N];
int main()
{
    freopen("park.in", "r", stdin);
    freopen("park.out", "w", stdout);
    scanf("%lld%lld", &t, &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &c[i]);
    priority_queue<pair<ld, ll>> q;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &h[i]);
        q.push({h[i] * 1.0 / c[i], i});
    }
    ll Answer = 0;
    while (q.size())
    {
        ll Index = q.top().second;
        q.pop();
        if (t < c[Index])
            continue;
        t -= c[Index];
        Answer += h[Index];
        h[Index] /= 2;
        q.push({h[Index] * 1.0 / c[Index], Index});
    }
    printf("%lld\n", Answer);
    return 0;
}
