#include <bits/stdc++.h>
using namespace std;
typedef long double lb;
const int N = 505;
lb p[N][N];
int m, n;
int main()
{
    freopen("bb5.in", "r", stdin);
    freopen("bb5.out", "w", stdout);
    cin >> m >> n;
    p[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            p[i][j] = p[i - 1][j] * j / m + p[i - 1][j - 1] * (m - j + 1) / m;
        }
    }
    lb ans = 0;
    for (int j = 1; j <= m; j++)
    {
        ans += p[n][j] * j;
    }
    cout << fixed << setprecision(3) << ans << endl;
    return 0;
}
