#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int m, n, a[N][N], f[N][N];
string s;
int main() {
//    freopen("sum.in", "r", stdin);
//    freopen("sum.out", "w", stdout);
    cin >> n >> m >> s;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        for (int j = 1; j < n; j++) {
            temp = temp * 10 + s[j] - '0';
            a[i][j] = temp;
        }
    }
    for (int i = 0; i < n; i++)
        f[i][0] = a[0][i];
    for (int i = 0; i < n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 0; k < i; k++)
                f[i][j] = max(f[k][j - 1] * a[k + 1][i], f[i][j]);
    cout << f[n - 1][m];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << f[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
