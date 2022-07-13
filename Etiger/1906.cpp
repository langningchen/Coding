#include <bits/stdc++.h>
using namespace std;
const int N = 55;
const int M = 10005;
const int MOD = 1000005;
long long n, m, x[N], f[N][M];
int main()
{
    freopen("amusement.in", "r", stdin);
    freopen("amusement.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            if (j < x[i])
                f[i][j] = f[i - 1][j] % MOD;
            else
                f[i][j] = f[i - 1][j] + f[i - 1][j - x[i]] % MOD;
    int ans = 0;
    for (int j = 0; j <= m; j++)
        ans += f[n][j] % MOD;
    cout << ans % MOD << endl;
    return 0;
}
