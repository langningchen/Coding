#include <bits/stdc++.h>
using namespace std;
const int N = 5015;
int m, n, f[N][N], s[N][N];
int main()
{
    freopen("reward2.in", "r", stdin);
    freopen("reward2.csv", "w", stdout);
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> f[i][j];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            s[i][j] = f[i][j] + s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1];
    cout << endl;
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
            cout << s[i][j] << ",";
        cout << endl;
    }
    return 0;
}
