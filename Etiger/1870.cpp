#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 105;
const ll MAXV = 100005;
const ll INF = 0x7FFFFFFFFFFFFFFF / 2;
ll n, W, w[N], v[N], g[N][MAXV];
int main()
{
    freopen("investment.in", "r", stdin);
    freopen("investment.out", "w", stdout);
    cin >> n >> W;
    for (ll i = 1; i <= n; i++)
        cin >> w[i] >> v[i];
    ll V = n * 1000;
    for (ll p = 1; p <= V; p++)
        g[0][p] = INF;
    g[0][0] = 0;
    for (ll i = 1; i <= n; i++)
        for (ll p = 0; p <= V; p++)
            if (v[i] > p)
                g[i][p] = min(g[i - 1][p], w[i]);
            else
                g[i][p] = min(g[i - 1][p], g[i - 1][p - v[i]] + w[i]);
    for (int p = V; p >= 0; p--)
        if (g[n][p] <= W)
        {
            cout << p << endl;
            break;
        }
    return 0;
}