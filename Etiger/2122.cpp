#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 4005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll n, ans, sL[2][N], gL[2][N], sR[2][N], gR[2][N], c[2][N], f[N][2];
void upd(ll &x, ll v)
{
    if (x > v)
        x = v;
}
void prefix(ll x)
{
    for (ll i = 1; i <= n; i++)
    {
        sL[x][i] = sL[x][i - 1] + c[x][i];
        gL[x][i] = gL[x][i - 1] + c[x][i] * i;
    }
    for (ll i = n; i >= 0; i--)
    {
        sR[x][i] = sR[x][i + 1] + c[x][i];
        gR[x][i] = gR[x][i + 1] + c[x][i] * (n - i + 1);
    }
}
ll moveRight(ll l, ll r, ll x)
{
    ll *s = sR[x];
    ll *g = gR[x];
    return g[l] - g[r + 1] - (s[l] - s[r + 1]) * (n - r);
}
ll moveLeft(ll l, ll r, ll x)
{
    ll *s = sL[x];
    ll *g = gL[x];
    return g[r] - g[l - 1] - (s[r] - s[l - 1]) * (l - 1);
}
ll cost(ll l, ll r, ll x)
{
    ll m = (l + r) / 2;
    return moveLeft(l, m, x) + moveRight(m + 1, r, x);
}
int main()
{
    freopen("dorm.in", "r", stdin);
    freopen("dorm.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> c[0][i] >> c[1][i];
    prefix(0);
    prefix(1);
    for (ll i = 1; i <= n - 1; i++)
        for (ll x = 0; x <= 1; x++)
        {
            f[i][x] = INF;
            if (i < n)
                upd(f[i][x], moveRight(1, i, x ^ 1));
            for (ll j = 1; j <= i - 1; j++)
                upd(f[i][x], f[j][x ^ 1] + cost(j + 1, i, x ^ 1));
        }
    ll ans = INF;
    for (ll i = 1; i <= n - 1; i++)
        for (ll x = 0; x <= 1; x++)
            upd(ans, f[i][x] + moveLeft(i + 1, n, x));
    cout << ans << endl;
    return 0;
}
