#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int MOD = 1000007;
int m, n, a[N], f[N][N];
int main() {
    freopen("flower.in", "r", stdin);
    freopen("flower.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i <= n; i++) {
        f[i][0] = 1;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 0; k <= min(j, a[i]); k++)
                f[i][j] = (f[i][j] + f[i - 1][j - k]) % MOD;
    cout << f[n][m] % MOD << endl;
    return 0;
}
