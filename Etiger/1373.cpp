#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 20;
const ll M = 165;
ll l, r, d[N];
ll f[N][M][M][2];
bool ok[N][M][M][2];
ll F(ll &MOD, ll p, ll s, ll r, bool lmt)
{
    if (p == 0)
        return !s && !r;
    if (ok[p][s][r][lmt])
        return f[p][s][r][lmt];
    ok[p][s][r][lmt] = 1;
    f[p][s][r][lmt] = 0;
    for (ll i = 0; i <= (lmt ? d[p] : 9); i++)
    {
        if (i > s)
            break;
        if (p * 9 < s)
            break;
        f[p][s][r][lmt] += F(MOD, p - 1, s - i, (r * 10 + i) % MOD, lmt && i == d[p]);
    }
    return f[p][s][r][lmt];
}
ll prefix(ll x, ll MOD)
{
    ll nD = 0;
    do
    {
        d[++nD] = x % 10;
        x /= 10;
    } while (x);
    ll res = 0;
    for (ll MOD = 1; MOD <= nD * 9; MOD++)
    {
        memset(ok, 0, sizeof(ok));
        res += F(MOD, nD, MOD, 0, 1);
    }
    return res;
}
void solve()
{
    cout << prefix(r, 1) - prefix(l - 1, 1) << endl;
}
int main()
{
    freopen("multiple.in", "r", stdin);
    freopen("multiple.out", "w", stdout);
    cin >> l >> r;
    solve();
    return 0;
}