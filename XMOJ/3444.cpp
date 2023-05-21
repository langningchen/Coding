#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2005;
const ll INF = 0x3FFF'FFFF'FFFF'FFFF;
ll n, m, f[N][N], v[N][N], res[N];
int main()
{
    scanf("%d%d", &n, &m);
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
        {
            scanf("%lld", &v[i][j]);
            f[i][j] = -INF;
        }
    for (ll i = 1; i <= n; i++)
        for (ll j = i; j <= m - (n - i); j++)
            for (ll k = i - 1; k < j; k++)
                f[i][j] = max(f[i][j], f[i - 1][k] + v[i][j]);
    printf("%lld\n", *max_element(f[n] + 1, f[n] + m + 1));
    return 0;
}
