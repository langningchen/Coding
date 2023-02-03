#include <bits/stdc++.h>
using namespace std;
const int N = 35;
const int INF = 0x7FFF'FFFF;
int m, f[N][N];
int main()
{
    freopen("timemachine.in", "r", stdin);
    freopen("timemachine.out", "w", stdout);
    cin >> m;
    for (int i = 1; i <= 24; i++)
        for (int j = 1; j <= 24; j++)
            f[i][j] = INF;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        f[x][y] = 1;
    }
    for (int k = 1; k <= 24; k++)
        for (int i = 1; i <= 24; i++)
            for (int j = 1; j <= 24; j++)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    bool ok = 0;
    for (int i = 1; i <= 23; i++)
        if (f[24][i] < INF)
        {
            ok = 1;
            cout << i << " " << f[24][i] << endl;
        }
    if (!ok)
        cout << "impossible" << endl;
    return 0;
}
