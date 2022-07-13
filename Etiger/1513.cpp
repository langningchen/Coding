#include <bits/stdc++.h>
using namespace std;
const int N = 405;
int n, t;
double f[N][N];
int main()
{
    freopen("casinoroyale1.in", "r", stdin);
    freopen("casinoroyale1.out", "w", stdout);
    cin >> n >> t;
    for (int i = 0; i <= n; i++)
    {
        f[0][i] = i;
    }
    for (int i = 1; i <= t; i++)
    {
        for (int j = 0; j < n; j++)
        {
            f[i][j] = (f[i - 1][j] + f[i - 1][j + 1]) / 2;
        }
        f[i][n] = (f[i - 1][n] + f[i - 1][n - 1]) / 2;
    }
    cout << fixed << setprecision(2) << f[t][0] << endl;
    return 0;
}
