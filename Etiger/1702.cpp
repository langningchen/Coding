#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
const ll N = 1005;
ll nR, nC, sR[N], a[N][2 * N], f[N][2 * N];
ll id(ll d)
{
    return d + nR + 1;
}
// ll fastscan()
// {
//     bool flag = false;
//     ll ans = 0;
//     char c = getchar();
//     if (c == '-')
//         flag = true;
//     else
//         ans = c - '0';
//     c = getchar();
//     while (c >= '0' && c <= '9')
//     {
//         ans *= 10;
//         ans += c - '0';
//         c = getchar();
//     }
//     return ans * (flag ? -1 : 1);
// }
int main()
{
    freopen("meal.in", "r", stdin);
    freopen("meal.out", "w", stdout);
    // nR = fastscan();
    // nC = fastscan();
    cin >> nR >> nC;
    for (ll r = 1; r <= nR; r++)
        for (ll c = 1; c <= nC; c++)
        {
            // a[r][c] = fastscan();
            cin >> a[r][c];
            sR[r] = (sR[r] + a[r][c]) % MOD;
        }
    ll ans = 1;
    for (ll r = 1; r <= nR; r++)
    {
        ans *= sR[r] + 1;
        ans %= MOD;
    }
    ans = (ans - 1 + MOD) % MOD;
    for (ll c = 1; c <= nC; c++)
    {
        // memset(f, 0, sizeof(f));
        f[0][id(0)] = 1;
        for (ll r = 1; r <= nR; r++)
            for (ll d = -r; d <= r; d++)
            {
                f[r][id(d)] = f[r - 1][id(d)];
                f[r][id(d)] += a[r][c] * f[r - 1][id(d - 1)];
                f[r][id(d)] += (sR[r] - a[r][c]) * f[r - 1][id(d + 1)];
                f[r][id(d)] %= MOD;
            }
        for (ll d = 1; d <= nR; d++)
            ans = (ans - f[nR][id(d)] + MOD) % MOD;
    }
    cout << ans << endl;
    return 0;
}