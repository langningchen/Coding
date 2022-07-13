#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int m, n, p[N];
double f[N];
int main()
{
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        p[x] = y;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (p[i] != 0)
        {
            f[i] = f[p[i]];
        }
        else
        {
            f[i] = (f[i + 1] + f[i + 2] + f[i + 3] + f[i + 4] + f[i + 5] + f[i + 6]) * 1.0 / 6 + 1;
        }
    }
    cout << fixed << setprecision(4) << f[0] << endl;
    return 0;
}
