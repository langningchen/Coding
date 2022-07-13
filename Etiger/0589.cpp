#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int INF = 0x7FFFFFFF;
int n, m, x[N], d[N], ok[N], a[N][N];
void Dijkstra()
{
    fill(d, d + n + 2, INF);
    d[1] = 0;
    for (int k = 1; k <= n; ++k)
    {
        int u = n + 1;
        for (int i = 1; i <= n; ++i)
            if (!ok[i] && d[i] < d[u])
                u = i;
        if (u == n + 1)
            break;
        ok[u] = 1;
        for (int j = 1; j <= n; ++j)
            d[j] = min(d[j], d[u] + a[u][j]);
    }
}
int main()
{
    freopen("conference.in", "r", stdin);
    freopen("conference.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> x[i];
    cin >> m;
    int u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v >> w;
        if (a[u][v] == 0)
            a[u][v] = a[v][u] = w;
        else
            a[u][v] = a[v][u] = min(a[u][v], w);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (a[i][j] == 0)
                a[i][j] = INF;
    Dijkstra();
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        if (d[i] != INF)
            ans += x[i] * d[i];
    cout << ans << endl;
    return 0;
}
