#include <bits/stdc++.h>
using namespace std;
const int N = 2003;
int n, m, k, a[N], MAX[N], q[N], f[N - 1][N];
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int j = 1; j <= m; j++) {
        int l = 0, r = 0;
        for (int i = j - 1; i <= n + 1 + j - m && i <= j * k; i++) {
            while (l < r && i - q[l] >= k) l++;
            while (l < r && f[i][j - 1] > f[q[r - 1]][j - 1]) r--;
            q[r++] = i;
            MAX[i] = f[q[l]][j - 1];
        }
        for (int i = j; i <= n + 1 + j - m && i <= j * k; i++)
            f[i][j] = MAX[i - 1] + a[i];
    }
//    for (int i = 0; i <= n; i++) {
//        for (int j = 0; j <= m; j++) {
//            cout << f[i][j] << " ";
//        }
//        cout << endl;
//    }
    if (f[n + 1][m] == 0) {
        cout << -1 << endl;
    }
    else {
        cout << f[n + 1][m] << endl;
    }
    return 0;
}
