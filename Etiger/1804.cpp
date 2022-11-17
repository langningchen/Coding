#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 200005;
ll n, d[N];
vector<ll> g[N];
void dfs_d(int a, int b)
{
    for (int i = 0; i < g[a].size(); i++)
    {
        int c = g[a][i];
        if (c == b)
            continue;
        d[c] = d[a] + 1;
        dfs_d(c, a);
    }
}
int main()
{
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        int a;
        cin >> a;
        g[a].push_back(i);
    }
    dfs_d(1, 0);
    ld ans = 0;
    for (ll i = 1; i <= n; i++)
        ans += 1.0 / (d[i] + 1);
    cout << fixed << setprecision(6) << ans << endl;
    return 0;
}