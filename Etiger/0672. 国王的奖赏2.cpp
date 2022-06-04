#include <bits/stdc++.h>
const int N = 501;
int m, n, f[N][N], s[N][N];
using namespace std;
int main() {
    freopen("reward2.in","r",stdin);
    freopen("reward2.csv","w",stdout);
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> f[i][j];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            s[i][j] = f[i][j] + s[i][j-1] + s[i-1][j] - s[i-1][j-1];
//    int ans = INT_MIN;
//    for (int i1 = 1; i1 <= m; i1++)
//        for (int j1 = 1; j1 <= n; j1++)
//            for (int i2 = 1; i2 <= m; i2++)
//                for (int j2 = 1; j2 <= n; j2++) {
//                    int cnt = s[i2][j2] - s[i2][j1 - 1] - s[i1 - 1][j2] + s[i1 - 1][j1 - 1];
//                    ans = max(ans, cnt);
//                }
//    cout << ans << endl;
    cout << endl;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++)
            cout << s[i][j] << ",";
        cout << endl;
    }
    return 0;
}
