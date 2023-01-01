#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
const int INF = 0x7FFFFFFF;
ll n, m, ans;
map<ll, ll> a[8];
int main()
{
    cin >> n >> m;
    if (m == 0)
    {
        for (int j = 1; j <= n; j++)
            for (int i = 1; i <= 6; i++)
                a[i][j] = (j == 1 ? 1 : (a[i - 1][j - 1] + a[i][j - 1] + a[i + 1][j - 1]) % MOD);
        for (int i = 1; i <= 6; i++)
            ans += a[i][n];
        // for (int i = 1; i <= 6; i++)
        //     for (int j = 1; j <= n; j++)
        //         cout << a[i][j] << " \n"[j == n];
        cout << ans % MOD << endl;
        return 0;
    }
    for (int i = 0; i < m; i++)
    {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for (ll x = x1; x <= x2; x++)
            for (ll y = y1; y <= y2; y++)
                a[x][y] = -INF;
    }
    for (int j = 1; j <= n; j++)
        for (int i = 1; i <= 6; i++)
            a[i][j] = (j == 1 ? 1 : (a[i][j] == -INF ? 0 : (a[i - 1][j - 1] + a[i][j - 1] + a[i + 1][j - 1]) % MOD));
    for (int i = 1; i <= 6; i++)
        ans = (ans + a[i][n]) % MOD;
    cout << ans % MOD << endl;
    return 0;
}