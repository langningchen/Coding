#include <bits/stdc++.h>
using namespace std;
const int N = 505;
const int INF = 10000;
int n, f[N][N];
int main() {
    freopen("rocket.in","r",stdin);
    freopen("rocket.out","w",stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> f[i][j];
            f[i][j] = f[i][j] == -1 ? INF : f[i][j];
            f[j][i] = f[i][j];
        }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    for (int i = 0; i < n; i++)
        cout << (f[0][i] == INF ? -1 : f[0][i]) << " ";
    return 0;
}
