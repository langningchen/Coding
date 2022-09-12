#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2005;
ll n, x[N], xs[N], g[N][N];
ll minCost()
{
    g[1][1] = abs(x[1] - xs[1]);
    for (ll j = 2; j <= n; j++)
        g[1][j] = min(g[1][j - 1], abs(x[1] - xs[j]));
    for (ll i = 2; i <= n; i++)
    {
        g[i][1] = g[i - 1][1] + abs(x[i] - xs[1]);
        for (ll j = 2; j <= n; j++)
            g[i][j] = min(g[i][j - 1], g[i - 1][j] + abs(x[i] - xs[j]));
    }
    return g[n][n];
}
int main()
{
    freopen("monotone.in", "r", stdin);
    freopen("monotone.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> x[i];
    for (ll j = 1; j <= n; j++)
        xs[j] = x[j];
    sort(xs + 1, xs + 1 + n);
    ll ans = minCost();
    reverse(x + 1, x + 1 + n);
    ans = min(ans, minCost());
    cout << ans << endl;
    return 0;
}