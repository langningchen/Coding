#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1000000007;
const int N = 2005;
ll n, m, a[N], f[N], C[N][N];
int main()
{
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
    C[0][0] = 1;
    for (int i = 1; i < N; i++)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> a[i];
    ll ans = 0;
    for (int i = 0; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j <= m; j++)
        {
            f[i] *= C[a[j] + n - i - 1][a[j]];
            f[i] %= MOD;
        }
        if (i & 1)
            ans -= C[n][i] * f[i];
        else
            ans += C[n][i] * f[i];
        ans = (ans % MOD + MOD) % MOD;
    }
    cout << ans << endl;
    return 0;
}
