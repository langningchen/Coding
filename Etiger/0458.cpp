/*
f[i][j]代表将整数n分成k份有多少种不同的分法
    j=0,1,2,3,4,5
i=0   0 0 0 0 0 0
i=1   0 1 0 0 0 0
i=2   0 1 1 0 0 0
i=3   0 1 1 1 0 0
i=4   0 1 1 1 1 0
i=5   0 1 1 1 1 1
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 401;
ll m, n, f[N][N];
int main() {
    freopen("trip.in","r",stdin);
    freopen("trip.out","w",stdout);
    cin >> m >> n;
    for(ll i = 1; i <= n; i++) f[i][1] = 1;
    for(ll j = 2; j <= m; j++)
        for(ll i = j; i <= n; i++)
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
    ll ans = 0;
    for(ll i = 1; i <= m;i++)
        ans += f[n][i];
    cout << ans << endl;
    return 0;
}
