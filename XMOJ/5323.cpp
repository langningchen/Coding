#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 9999973;
const ll N = 105;
ll n, m, ans, dp[N][N][N];
int main()
{
    scanf("%lld%lld", &n, &m);
    dp[0][0][0] = 1;
    for (ll i = 1; i <= n; i++)
        for (ll j = 0; j <= m; j++)
            for (ll k = 0; k + j <= m && k <= 2 * i; k++)
            {
                dp[i][j][k] += dp[i - 1][j][k];
                if (k >= 1)
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j + 1][k - 1] * (j + 1) + dp[i - 1][j][k - 1] * j % MOD * (m - j + 1 - k)) % MOD;
                if (k >= 2)
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j + 2][k - 2] * (j + 1) * (j + 2) / 2) % MOD;
                if (j >= 1)
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - 1][k] * (m - j - k + 1)) % MOD;
                if (j >= 2)
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - 2][k] * (m - k - j + 1) * (m - k - j + 2) / 2) % MOD;
            }
    for (ll i = 0; i <= m; i++)
        for (ll j = 0; i + j <= m && (i + j) <= 2 * n; j++)
            ans = (ans + dp[n][i][j]) % MOD;
    printf("%lld\n", ans);
    return 0;
}
