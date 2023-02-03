#include <bits/stdc++.h>
using namespace std;
const int N = 805;
const int INF = 0x7FFF'FFFF;
int n, m, y[N], f[N][N];
int main()
{
    freopen("variety.in", "r", stdin);
    freopen("variety.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> y[i];
    for (int i = 1; i <= n; i++)
        f[i][1] = 0;
    for (int j = 2; j <= m; j++)
        for (int i = j; i <= n; i++)
        {
            f[i][j] = INF;
            for (int k = j - 1; k < i; k++)
                f[i][j] = min(f[i][j], f[k][j - 1] + abs(y[i] - y[k]));
        }
    int ans = INF;
    for (int i = m; i <= n; i++)
        ans = min(ans, f[i][m]);
    cout << ans << endl;
    return 0;
}
