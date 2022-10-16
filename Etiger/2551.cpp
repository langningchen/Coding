#include <bits/stdc++.h>
using namespace std;
const int N = 15;
int n, m, d[N], f[N][2][2];
bool ok[N][2][2];
int F(int p, bool lmt, bool pre1)
{
    if (p == 0)
        return 1;
    if (ok[p][lmt][pre1])
        return f[p][lmt][pre1];
    ok[p][lmt][pre1] = 1;
    f[p][lmt][pre1] = 0;
    for (int i = 0; i <= (lmt ? d[p] : 9); i++)
    {
        if (i == 4)
            continue;
        if (pre1 && i == 3)
            continue;
        f[p][lmt][pre1] += F(p - 1, lmt && i == d[p], i == 1);
    }
    return f[p][lmt][pre1];
}
int solve(int x)
{
    memset(ok, 0, sizeof(ok));
    memset(f, 0, sizeof(f));
    int nD = 0;
    do
    {
        d[++nD] = x % 10;
        x /= 10;
    } while (x);
    return F(nD, 1, 0);
}
int main()
{
    freopen("thirteen.in", "r", stdin);
    freopen("thirteen.out", "w", stdout);
    cin >> m >> n;
    cout << solve(n) - solve(m - 1) << endl;
    return 0;
}