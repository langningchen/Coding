#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int f[N][N];
int main() {
    freopen("lcs.in", "r", stdin);
    freopen("lcs.out", "w", stdout);
    string a, b;
    cin >> a >> b;
    int n = a.size();
    int m = b.size();
    a = " " + a; b = " " + b;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j])
                f[i][j] = f[i - 1][j - 1] + 1;
            else
                f[i][j] = max(f[i][j - 1], f[i - 1][j]);
        }
    }
    cout << f[n][m] << endl;
    return 0;
}
