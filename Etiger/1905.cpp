#include <bits/stdc++.h>
using namespace std;
const int N = 21;
const int M = 101;
int n, x[N], f[N][M];
int main()
{
    freopen("currency.in", "r", stdin);
    freopen("currency.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 100; j++)
            if (j < x[i])
                f[i][j] = f[i - 1][j];
            else
                f[i][j] = f[i - 1][j] or f[i - 1][j - x[i]];
    int ans = 0;
    for (int j = 1; j <= 100; j++)
        if (f[n][j])
            ans++;
    cout << 100 - ans << endl;
    return 0;
}
