#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
ll n, d[N], sz[N];
vector<ll> g[N];
void dfs_sz_d(int a, int b)
{
    sz[a] = 1;
    for (int i = 0; i < g[a].size(); i++)
    {
        int c = g[a][i];
        if (c == b)
            continue;
        d[c] = d[a] + 1;
        dfs_sz_d(c, a);
        sz[a] += sz[c];
    }
}
int main()
{
    freopen("bridge2.in", "r", stdin);
    freopen("bridge2.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs_sz_d(1, 0);
    ll ans = 0, nOddD = 0;
    for (ll u = 1; u <= n; u++)
    {
        ans += sz[u] * (n - sz[u]);
        nOddD += (d[u] & 1);
    }
    ans += nOddD * (n - nOddD);
    ans /= 2;
    cout << ans << endl;
    return 0;
}