#include <bits/stdc++.h>
using namespace std;
const int N = 55;
typedef long long ll;
ll f[N][N][5][5];
char ma[N][N];
ll T, n, m;
int main()
{
    freopen("home.in", "r", stdin);
    freopen("home.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> T;
    while (T-- > 0)
    {
        memset(f, 0, sizeof(f));
        cin >> n >> m;
        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= n; j++)
                cin >> ma[i][j];
        for (ll i = 1; i <= n; i++)
        {
            if (ma[i][1] != '.')
                break;
            f[i][1][0][0] = f[i][1][1][1] = 1;
        }
        for (ll i = 1; i <= n; i++)
        {
            if (ma[1][i] != '.')
                break;
            f[1][i][0][1] = f[1][i][1][0] = 1;
        }
        for (ll i = 2; i <= n; i++)
            for (ll j = 2; j <= n; j++)
                if (ma[i][j] == '.')
                    for (ll k = 1; k <= m; k++)
                        for (ll l = 0; l < 2; l++)
                            f[i][j][k][l] = f[i][j - 1][k - (l == 0)][1] + f[i - 1][j][k - (l == 1)][0];
        ll ans = 0;
        for (ll k = 1; k <= m; k++)
            for (ll l = 0; l < 2; l++)
            {
                f[n][n][k][l] -= f[n][n][k - 1][l];
                ans += f[n][n][k][l];
            }
        cout << ans << endl;
    }
    return 0;
}