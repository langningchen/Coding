#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 15;
ll n, m, d[N], f[N][N][2][2];
bool ok[N][N][2][2];
ll F(ll p, ll pre, bool lmt, bool lead0)
{
    if (p == 0)
        return 1;
    if (ok[p][pre][lmt][lead0])
        return f[p][pre][lmt][lead0];
    ok[p][pre][lmt][lead0] = 1;
    f[p][pre][lmt][lead0] = 0;
    for (ll i = 0; i <= (lmt ? d[p] : 9); i++)
    {
        if (!lead0 && abs(i - pre) < 2)
            continue;
        f[p][pre][lmt][lead0] += F(p - 1, i, lmt && i == d[p], lead0 && i == 0);
    }
    return f[p][pre][lmt][lead0];
}
ll solve(ll x)
{
    memset(ok, 0, sizeof(ok));
    memset(f, 0, sizeof(f));
    ll nD = 0;
    while (x)
    {
        d[++nD] = x % 10;
        x /= 10;
    }
    return F(nD, 0, 1, 1);
}
int main()
{
    freopen("volatility.in", "r", stdin);
    freopen("volatility.out", "w", stdout);
    ll n, m;
    cin >> n >> m;
    cout << solve(m) - solve(n - 1) << endl;
    return 0;
}
