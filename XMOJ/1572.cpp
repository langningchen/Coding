#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 305;
ll n, m, f[N][N];
vector<ll> to[N];
ll dfs(ll u)
{
    ll CurrentSize = 1;
    for (ll i = 0; i < to[u].size(); i++)
    {
        ll v = to[u][i];
        ll Size = dfs(v);
        for (ll i = min(CurrentSize, m + 1); i > 0; i--)
            for (ll j = 1; j <= Size && i + j <= m + 1; j++)
                f[u][i + j] = max(f[u][i + j], f[u][i] + f[v][j]);
        CurrentSize += Size;
    }
    return CurrentSize;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        ll k;
        scanf("%lld%lld", &k, &f[i][1]);
        to[k].push_back(i);
    }
    dfs(0);
    printf("%lld\n", f[0][m + 1]);
    return 0;
}
