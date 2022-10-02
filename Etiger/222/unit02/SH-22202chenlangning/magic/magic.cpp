#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
int n, m, k;
vector<ll> to[N];
vector<ll> w[N];
ll d[N][N];
bool vst[N];
// void dijkstra()
// {
//     memset(d, 0x7FFFFFFF, sizeof(d));
//     memset(vst, 0, sizeof(vst));
//     d[0] = 0;
//     while (1)
//     {
//         int x = -1;
//         for (int j = 0; j < n; j++)
//             if (!vst[j] && (x == -1 || d[j] < d[x]))
//                 x = j;
//         if (x == -1)
//             break;
//         vst[x] = 1;
//         for (size_t j = 0; j < to[x].size(); j++)
//             d[to[x][j]] = min(d[to[x][j]], d[x] + w[x][j]);
//     }
// }
void floyd()
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
int main()
{
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    cin >> n >> m >> k;
    if (n == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 0; i < m; i++)
    {
        ll u, v, t;
        cin >> u >> v >> t;
        u--;
        v--;
        d[u][v] = t;
        to[u].push_back(v);
        w[u].push_back(t);
    }
    // dijkstra();
    for (int i = 0; i < n; i++)
        d[i][i] = 0;
    floyd();
    cout << d[0][n - 1] << endl;
    return 0;
}
