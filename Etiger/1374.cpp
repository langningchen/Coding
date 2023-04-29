#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 20;
ll l, r, d[N];
ll f[N][10][10][3][2];
bool ok[N][10][10][3][2];
ll F(ll p, ll pre1, ll pre2, ll lead, bool lmt)
{
    if (p == 0)
        return 1;
    if (ok[p][pre1][pre2][lead][lmt])
        return f[p][pre1][pre2][lead][lmt];
    ok[p][pre1][pre2][lead][lmt] = 1;
    f[p][pre1][pre2][lead][lmt] = 0;
    for (ll i = 0; i <= (lmt ? d[p] : 9); i++)
    {
        if (lead >= 1 && i == pre1)
            continue;
        if (lead == 2 && i == pre2)
            continue;
        ll L = (i || lead ? lead + 1 : 0);
        if (L > 2)
            L = 2;
        f[p][pre1][pre2][lead][lmt] += F(p - 1, i, pre1, L, lmt && i == d[p]);
    }
    return f[p][pre1][pre2][lead][lmt];
}
ll prefix(ll x)
{
    memset(ok, 0, sizeof(ok));
    memset(f, 0, sizeof(f));
    ll nD = 0;
    do
    {
        d[++nD] = x % 10;
        x /= 10;
    } while (x);
    return F(nD, 0, 0, 0, 1);
}
void solve()
{
    cout << prefix(r) - prefix(l - 1) << endl;
}
int main()
{
    freopen("palindrome.in", "r", stdin);
    freopen("palindrome.out", "w", stdout);
    cin >> l >> r;
    solve();
    return 0;
}
