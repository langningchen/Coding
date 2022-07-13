#include <bits/stdc++.h>
using namespace std;
const int N = 12;
const int MOD = 100000000;
int m, n, ans, mp[N], f[N + 1][(1 << N)];
int OK(int i, int p)
{
    return (mp[i] | p) == mp[i] && (p & (p >> 1)) == 0;
}
int main()
{
    freopen("plan3.in", "r", stdin);
    freopen("plan3.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int temp;
            cin >> temp;
            mp[i] += temp;
            mp[i] *= 2;
        }
        mp[i] /= 2;
    }
    int nPtn = (1 << m);
    for (int p = 0; p < nPtn; p++)
        f[1][p] = OK(1, p);
    for (int i = 2; i <= n; i++)
        for (int p = 0; p < nPtn; p++)
            if (OK(i, p))
            {
                for (int q = 0; q < nPtn; q++)
                    if (OK(i - 1, q))
                    {
                        if (p & q)
                            continue;
                        f[i][p] = (f[i][p] + f[i - 1][q]) % MOD;
                    }
            }
    for (int u = 0; u <= 1 << m; u++)
    {
        ans = (ans + f[n][u]) % MOD;
    }
    cout << ans << endl;
    return 0;
}
