#include <bits/stdc++.h>
using namespace std;
const int N = 51;
const int M = 10001;
long long n, m, x[N], f[N][M];
int main() {
    freopen("amusement.in","r",stdin);
    freopen("amusement.out","w",stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> x[i];
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            if (j < x[i])
                f[i][j] = f[i - 1][j] % 1000007;
            else
                f[i][j] = f[i - 1][j] + f[i - 1][j - x[i]] % 1000007;
//    for (int i = 0; i <= n; i++) {
//        for (int j = 0; j <= m; j++)
//            cout << f[i][j];
//        cout << endl;
//    }
    int ans = 0;
    for (int j = 0; j <= m; j++)
        ans += f[n][j] % 1000007;
    cout << ans % 1000007 << endl;
    return 0;
}
