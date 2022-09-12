#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
const int INF = 0x7FFFFFFF;
ll n, x, a[N], b[N], d[N], f[N], g[N];
int main()
{
    freopen("future.in", "r", stdin);
    freopen("future.out", "w", stdout);
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (ll i = 1; i <= n; i++)
        b[i] = a[i] - x;
    for (ll i = 1; i <= n; i++)
        d[i] = INF;
    for (ll i = 1; i <= n; i++)
    {
        ll id = lower_bound(d + 1, d + 1 + n, b[i]) - d;
        d[id] = b[i];
        f[i] = id;
    }
    for (ll i = 1; i <= n; i++)
        d[i] = INF;
    for (ll i = n; i >= 1; i--)
    {
        ll id = lower_bound(d + 1, d + 1 + n, -b[i]) - d;
        g[i] = id;
        id = lower_bound(d + 1, d + 1 + n, -a[i]) - d;
        d[id] = -a[i];
    }
    ll ans = -INF;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, f[i] + g[i] - 1);
    }
    cout << ans << endl;
    return 0;
}