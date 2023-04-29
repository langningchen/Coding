#include <bits/stdc++.h>
using namespace std;
const int N = 6;
const int M = 105;
int x[N], f[N][M];
int main()
{
    freopen("santa.in", "r", stdin);
    freopen("santa.out", "w", stdout);
    for (int i = 1; i <= 5; i++)
        cin >> x[i];
    f[0][0] = 0;
    for (int i = 1; i <= 5; i++)
        for (int j = 0; j <= 100; j++)
            if (j < x[i])
                f[i][j] = f[i - 1][j];
            else
                f[i][j] = max(f[i - 1][j], f[i - 1][j - x[i]] + x[i]);
    cout << f[5][100] << endl;
    return 0;
}
