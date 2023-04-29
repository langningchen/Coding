#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 20;
ll l, r, d[N], f[10][N][2][2], cnt[N][2];
bool ok[10][N][2][2];
ll F(ll T, ll p, bool lmt, bool lead0)
{
    if (p == 0)
        return 0;
    if (ok[T][p][lmt][lead0])
        return f[T][p][lmt][lead0];
    ok[T][p][lmt][lead0] = 1;
    f[T][p][lmt][lead0] = 0;
    for (ll i = 0; i <= (lmt ? d[p] : 9); i++)
    {
        if (i == T && !(i == 0 && lead0))
            f[T][p][lmt][lead0] += cnt[p - 1][lmt && i == d[p]];
        f[T][p][lmt][lead0] += F(T, p - 1, lmt && i == d[p], lead0 && i == 0);
    }
    return f[T][p][lmt][lead0];
}
ll prefix(ll T, ll x)
{
    memset(ok, 0, sizeof(ok));
    memset(f, 0, sizeof(f));
    ll y = x;
    ll nD = 0;
    do
    {
        d[++nD] = x % 10;
        x /= 10;
    } while (x);
    cnt[0][0] = 1;
    cnt[0][1] = 1;
    for (ll p = 1; p <= nD; p++)
    {
        cnt[p][0] = cnt[p - 1][0] * 10;
        cnt[p][1] = y % cnt[p][0] + 1;
    }
    return F(T, nD, 1, 1);
}
void solve()
{
    for (ll T = 0; T <= 9; T++)
        cout << prefix(T, r) - prefix(T, l - 1) << " ";
    cout << endl;
}
int main()
{
    freopen("statistics.in", "r", stdin);
    freopen("statistics.out", "w", stdout);
    cin >> l >> r;
    solve();
    return 0;
}