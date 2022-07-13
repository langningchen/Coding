#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
ll m, n, f[N][N];
ll gcd(ll a, ll b)
{
    ll r = a % b;
    return r ? gcd(b, r) : b;
}
int main()
{
    freopen("flight.in", "r", stdin);
    freopen("flight.out", "w", stdout);
    cin >> m >> n;
    f[0][0] = 1;
    for (ll i = 1; i <= m; i++)
    {
        f[i][0] = f[i - 1][0] * 6;
        for (ll j = 1; j <= n; j++)
            for (ll k = 1; k <= 6; k++)
                f[i][j] += f[i - 1][max(0LL, j - k)];
    }
    ll numerator = f[m][n];
    ll denominator = f[m][0];
    if (numerator == 0)
    {
        cout << 0 << endl;
        return 0;
    }
    ll g = gcd(denominator, numerator);
    numerator /= g;
    denominator /= g;
    if (denominator == 1)
    {
        cout << numerator << endl;
    }
    else
    {
        cout << numerator << "/" << denominator << endl;
    }
    return 0;
}
