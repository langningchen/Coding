#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 205;
ll n, m, f[N][N];
int main()
{
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        f[i][1] = 1;
    for (int j = 2; j <= m; j++)
        for (int i = j; i <= n; i++)
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
    cout << f[n][m] << endl;
    return 0;
}
