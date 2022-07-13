#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m, cnt, d[N][N], in[N], vst[N], topo[N];
int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        if (d[b][a])
            continue;
        d[b][a] = 1;
        in[a]++;
    }
    for (int k = 1, i; k <= n; k++)
    {
        for (i = 1; i <= n; i++)
            if (!vst[i] && in[i] == 0)
                break;
        topo[++cnt] = i;
        vst[i] = cnt;
        for (int j = 1; j <= n; j++)
            if (d[i][j])
                d[i][j] = 0, in[j]--;
    }
    for (int i = 1; i <= n; i++)
        cout << topo[i] << " ";
    return 0;
}
