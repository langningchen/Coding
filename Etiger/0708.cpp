#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int n, m, a[N], h[N][N], f[N][N];
string s;
int main() {
    freopen("missile3.in", "r", stdin);
    freopen("missile3.out", "w", stdout);
    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++)
        a[i] = (s[i - 1] == 'F') ? 0 : 1;
    for (int j = 0; j <= m; j++)
        for (int i = j; i <= n; i++)
            h[i][j] = (a[i] == j % 2);
    for (int i = 1; i <= n; i++)
        f[i][0]= h[i][0] + f[i - 1][0];
    for (int j = 1; j <= m; j++)
        for (int i = j; i <= n; i++)
            f[i][j] = h[i][j] + max(f[i - 1][j], f[i - 1][j - 1]);
    cout << *max_element(f[n], f[n] + m + 1) << endl;
    return 0;
}
