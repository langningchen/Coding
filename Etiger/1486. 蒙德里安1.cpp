#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const int N = 1001;
int s[N][N], d[N][N], a, b, x, y, n, p;
int main() {
    freopen("mondrian.in","r",stdin);
    freopen("mondrian.out","w",stdout);
    cin >> n >> p;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            d[i][j] = s[i][j - 1] - s[i][j];
    for (int i = 1; i <= p; i++) {
        cin >> a >> b >> x >> y;
        for (int j = a; j <= x; j++)
            d[j][b]++, d[j][y + 1]--;
    }
    int ans = n * n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            s[i][j] = s[i][j - 1] + d[i][j];
            if (s[i][j]) ans--;
        }
    cout << ans << endl;
    return 0;
}
