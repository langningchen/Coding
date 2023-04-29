#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 0x7FFF'FFFF;
const int N = 50005;
ll c, n, g, f[2][N];
vector<ll> w[N];
vector<ll> v[N];
int main()
{
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    cin >> c >> n >> g;
    for (int i = 1; i <= n; i++)
    {
        int wi, vi, p;
        cin >> wi >> vi >> p;
        w[p].push_back(wi);
        v[p].push_back(vi);
    }
    for (ll j = 1; j <= c; j++)
        f[0][j] = -INF;
    for (ll i = 1; i <= g; i++)
        for (ll j = 0; j <= c; j++)
        {
            f[i % 2][j] = -INF;
            for (ll k = 0; k < w[i].size(); k++)
                if (j >= w[i][k] && f[abs(i % 2 - 1)][j - w[i][k]] >= 0)
                    f[i % 2][j] = max(f[i % 2][j], f[abs(i % 2 - 1)][j - w[i][k]] + v[i][k]);
        }
    ll ans = -INF;
    for (int i = 0; i <= c; i++)
        ans = max(ans, f[g % 2][i]);
    cout << ans << endl;
    return 0;
}
