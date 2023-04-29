#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, -1, 1, 0};
ll m, n, ans, ok[N][N], f[N][N], h[N][N], g[N][N];
ll F(ll x, ll y)
{
    if (ok[x][y])
    {
        return f[x][y];
    }
    ok[x][y] = 1;
    f[x][y] = 0;
    for (ll k = 0; k < 4; k++)
    {
        ll nx = x + dx[k], ny = y + dy[k];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && h[nx][ny] < h[x][y])
        {
            f[x][y] = max(f[x][y], F(nx, ny));
        }
    }
    f[x][y] += g[x][y];
    return f[x][y];
}
int main()
{
    cin >> m >> n;
    for (ll i = 0; i < m; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            cin >> h[i][j];
        }
    }
    for (ll i = 0; i < m; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            cin >> g[i][j];
        }
    }
    for (ll i = 0; i < m; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            ans = max(ans, F(i, j));
        }
    }
    cout << ans << endl;
    return 0;
}
