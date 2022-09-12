#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, f[N][N];
int main()
{
    freopen("inequality.in", "r", stdin);
    freopen("inequality.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char x, y, z;
        cin >> x >> y >> z;
        int u = x - 'a';
        int v = z - 'a';
        if (y == '>')
            f[u][v] = 1;
        else
            f[v][u] = 1;
    }
    for (int k = 0; k <= 25; k++)
        for (int i = 0; i <= 25; i++)
            for (int j = 0; j <= 25; j++)
                f[i][j] = f[i][j] || f[i][k] && f[k][j];
    for (int i = 0; i <= 25; i++)
        if (f[i][i] != 0)
        {
            cout << "impossible" << endl;
            return 0;
        }
    cout << "possible" << endl;
    return 0;
}
