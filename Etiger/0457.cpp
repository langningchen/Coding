#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305;
long long n, k, f[N][N];
int main()
{
    freopen("training.in", "r", stdin);
    freopen("training.out", "w", stdout);
    cin >> n >> k;
    for (ll i = 1; i <= n; i++)
        f[i][1] = 1;
    for (ll j = 2; j <= k; j++)
        for (ll i = j; i <= n; i++)
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
    ll ans = 0;
    for (ll i = 1; i <= k; i++)
        ans += f[n][i];
    cout << ans << endl;
    return 0;
}
