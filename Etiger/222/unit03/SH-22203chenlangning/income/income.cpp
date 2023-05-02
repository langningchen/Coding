#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 300005;
ll n, a, x[N], f[N];
bool IsSame()
{
    for (ll i = 1; i < n; i++)
        if (x[i] != x[i - 1])
            return false;
    return true;
}
void SolveSame()
{
    cout << (x[0] == a ? n * (n + 1) / 2 : 0) << endl;
}
bool Is1000()
{
    return n <= 1000;
}
void Solve1000()
{
    ll ans = 0;
    for (ll i = 0; i < n; i++)
        for (ll j = i; j < n; j++)
        {
            ll sum = 0;
            for (ll k = i; k <= j; k++)
                sum += x[k];
            if (sum * 1.0 / (j - i + 1) == a)
                ans++;
        }
    cout << ans << endl;
}
bool Is18000()
{
    return n <= 18000;
}
void Solve18000()
{
    for (ll i = 1; i <= n; i++)
        f[i] = f[i - 1] + x[i - 1];
    ll ans = 0;
    for (ll i = 1; i <= n; i++)
        for (ll j = i; j <= n; j++)
            if ((f[j] - f[i - 1]) * 1.0 / (j - i + 1) == a)
                ans++;
    cout << ans << endl;
}
void Solve()
{
}
int main()
{
    freopen("income.in", "r", stdin);
    freopen("income.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> a;
    for (ll i = 0; i < n; i++)
        cin >> x[i];
    if (IsSame())
        SolveSame();
    else if (Is1000())
        Solve1000();
    else if (Is18000())
        Solve18000();
    else
        Solve();
    return 0;
}