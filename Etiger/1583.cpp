#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int m, n, a, b, c, d, f[N][N], s[N][N];
int main()
{
    freopen("reward0.in", "r", stdin);
    freopen("reward0.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> f[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            s[i][j] = f[i][j] + s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1];
    int ans = INT_MIN;
    cin >> m;
    for (int k = 1; k <= m; k++)
    {
        cin >> a >> b >> c >> d;
        int cnt = s[c][d] - s[c][b - 1] - s[a - 1][d] + s[a - 1][b - 1];
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}
