#include <bits/stdc++.h>
using namespace std;
const int N = 5005;
double f[N][N];
int main()
{
    freopen("casino.in", "r", stdin);
    freopen("casino.out", "w", stdout);
    int r, b;
    cin >> r >> b;
    for (int i = 1; i <= r; i++)
    {
        f[i][0] = i;
        for (int j = 1; j <= b; j++)
        {

            f[i][j] = (f[i - 1][j] + 1) * i / (i + j) + (f[i][j - 1] - 1) * j / (i + j);
            f[i][j] = max(0.0, f[i][j]);
        }
    }
    cout << fixed << setprecision(3);
    cout << floor(f[r][b] * 1000) / 1000.0 << endl;
    return 0;
}