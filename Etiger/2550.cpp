#include <bits/stdc++.h>
using namespace std;
const int N = 15;
int d[N], f[N][2];
bool ok[N][2];
int F(int p, bool lmt)
{
    if (p == 0)
        return 1;
    if (ok[p][lmt])
        return f[p][lmt];
    ok[p][lmt] = 1;
    for (int i = 0; i <= (lmt ? d[p] : 9); i++)
    {
        if (i == 4)
            continue;
        f[p][lmt] += F(p - 1, lmt && i == d[p]);
    }
    return f[p][lmt];
}
int main()
{
    freopen("four.in", "r", stdin);
    freopen("four.out", "w", stdout);
    int x;
    cin >> x;
    int nD = 0;
    do
    {
        d[++nD] = x % 10;
        x /= 10;
    } while (x);
    cout << F(nD, 1) - 1 << endl;
    return 0;
}