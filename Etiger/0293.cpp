#include <bits/stdc++.h>
using namespace std;
const int N = 25;
long long lm[N][N];
int m, n, a, b;
int main()
{
    freopen("beast.in", "r", stdin);
    freopen("beast.out", "w", stdout);
    lm[1][1] = 1;
    cin >> n >> m >> a >> b;
    if (a == 1 && b == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (i != 1 || j != 1)
                if (i != a || j != b)
                    lm[i][j] = (lm[i][j - 1] + lm[i - 1][j]);
                else
                    lm[i][j] = 0;
    cout << lm[n][m] << endl;
    return 0;
}
