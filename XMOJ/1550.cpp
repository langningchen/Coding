#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 305;
const ll INF = 0x3FFF'FFFF'FFFF'FFFF;
ll n, a[N], dp[N][N];
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n + 1; i++)
        scanf("%lld", &a[i]);
    for (ll len = 2; len <= n; len++)
        for (ll i = 1; i <= n - len + 1; i++)
        {
            ll j = i + len - 1;
            dp[i][j] = INF;
            for (ll k = i; k < j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + a[i] * a[k + 1] * a[j + 1]);
        }
    printf("%lld\n", dp[1][n]);
    return 0;
}
