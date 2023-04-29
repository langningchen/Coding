#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int M = 1005;
const int INF = 0x7FFF'FFFF;
int n, ans, z[N], r[N], g[N][N * M * 2];
int id(int i)
{
    return i + N * M;
}
int main()
{
    freopen("merits.in", "r", stdin);
    freopen("merits.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> z[i] >> r[i];
    int mx = 0, mn = 0;
    for (int i = 1; i <= n; i++)
    {
        if (z[i] > 0)
            mx += z[i];
        else
            mn += z[i];
    }
    for (int j = 1; j <= mx; j++)
        g[0][id(j)] = -INF;
    for (int i = 1; i <= n; i++)
        for (int j = mn; j <= mx; j++)
        {
            g[i][id(j)] = g[i - 1][id(j)];
            int pre = j - z[i];
            if (pre > mx)
                continue;
            if (pre < mn)
                pre = mn;
            if (g[i - 1][id(pre)] == -INF)
                continue;
            g[i][id(j)] = max(g[i][id(j)], g[i - 1][id(pre)] + r[i]);
        }
    ans = 0;
    for (int j = 0; j <= mx; j++)
    {
        if (g[n][id(j)] < 0)
            continue;
        ans = max(ans, j + g[n][id(j)]);
    }
    cout << ans << endl;
    return 0;
}
