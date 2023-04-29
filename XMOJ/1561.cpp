#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1'000'000'007;
ll n, m;
ll f[1005][(1 << 5) + 5];
void dfs(ll i, ll j, ll state, ll nex)
{
    if (j == n)
        f[i + 1][nex] = (f[i + 1][nex] + f[i][state]) % MOD;
    else if ((state & (1 << j)) > 0)
        dfs(i, j + 1, state, nex);
    else if ((state & (1 << j)) == 0)
    {
        dfs(i, j + 1, state, (nex | (1 << j)));
        if (j + 1 < n && (state & (1 << j + 1)) == 0)
            dfs(i, j + 2, state, nex);
    }
}
int main()
{
    freopen("board.in", "r", stdin);
    freopen("board.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    f[1][0] = 1;
    for (ll i = 1; i <= m; i++)
        for (ll j = 0; j < 1 << n; j++)
            dfs(i, 0, j, 0);
    printf("%lld\n", f[m + 1][0]);
    return 0;
}
