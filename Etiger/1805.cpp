#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
typedef long double ld;
ld n, ans;
bitset<N> G[N];
void floyd()
{
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            if (G[v][u])
                G[v] |= G[u];
    ans = 0;
    for (int u = 1; u <= n; u++)
    {
        int cnt = 0;
        for (int v = 1; v <= n; v++)
            cnt += G[v][u];
        ans += 1. / cnt;
    }
}
int main()
{
    freopen("air.in", "r", stdin);
    freopen("air.out", "w", stdout);
    cin >> n;
    for (int u = 1; u <= n; u++)
        G[u][u] = 1;
    for (int u = 1; u <= n; u++)
    {
        int k, v;
        cin >> k;
        while (k--)
        {
            cin >> v;
            G[u][v] = 1;
        }
    }
    floyd();
    cout << fixed << setprecision(5) << ans << endl;
    return 0;
}
