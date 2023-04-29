#include <bits/stdc++.h>
using namespace std;
const int N = 17;
const int INF = 0x7FFF'FFFF;
int n, x[N][N], ptn[(1 << N)], f[N][(1 << N)];
int OK(int p)
{
    return (p & (p >> 1)) == 0;
}
int s(int i, int p)
{
    int sum = 0;
    for (int j = 0; j < n; j++)
        if (p & (1 << j))
            sum += x[i][n - j];
    return sum;
}
int main()
{
    freopen("plan2.in", "r", stdin);
    freopen("plan2.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> x[i][j];
    int nPtn = (1 << n);
    int nOK = 0;
    for (int p = 0; p < nPtn; p++)
        if (OK(p))
            ptn[nOK++] = p;
    for (int i = 1; i <= n; i++)
        for (int p = 0; p < nOK; p++)
        {
            int bst = -INF;
            for (int q = 0; q < nOK; q++)
            {
                if (ptn[p] & ptn[q])
                    continue;
                bst = max(bst, f[i - 1][ptn[q]]);
            }
            f[i][ptn[p]] = bst + s(i, ptn[p]);
        }
    int ans = -INF;
    for (int i = 0; i < nOK; i++)
        ans = max(ans, f[n][ptn[i]]);
    cout << ans << endl;
    return 0;
}
