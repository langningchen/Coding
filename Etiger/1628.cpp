#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20;
ll n, m, f[N][N];
int main()
{
    freopen("qiuhe1.in", "r", stdin);
    freopen("qiuhe1.out", "w", stdout);
    cin >> n >> m;
    if (n < m)
    {
        cout << 0 << endl;
        return 0;
    }
    for (ll i = 1; i <= n; i++)
        f[i][1] = 1;
    for (ll j = 2; j <= m; j++)
        for (ll i = j; i <= n; i++)
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
    cout << f[n][m] << endl;
    return 0;
}
