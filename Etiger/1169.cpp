#include <bits/stdc++.h>
using namespace std;
const int N = 505;
typedef long long ll;
ll c, n, W, V, w[N], v[N], f[N][N], p[N], vi, pi, wi;
int main()
{
    cin >> n >> V >> W;
    for (ll i = 1; i <= n; i++)
        cin >> v[i];
    for (ll i = 1; i <= n; i++)
        cin >> p[i];
    for (ll i = 1; i <= n; i++)
        cin >> w[i];
    for (ll i = 1; i <= n; i++)
        for (ll j = v[i]; j <= V; j++)
            for (ll k = w[i]; k <= W; k++)
                f[j][k] = max(f[j][k], f[j - v[i]][k - w[i]] + p[i]);
    cout << f[V][W] << endl;
    return 0;
}
