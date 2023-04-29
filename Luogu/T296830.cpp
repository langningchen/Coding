#include <bits/stdc++.h>
using namespace std;
const int N = 5005;
const int INF = 0x3FFFFFFF;
int n, m, q, st, l[N][N], ans1, ans2, st1, st2;
void dijkstra(int s)
{
    bool vis[N];
    memset(vis, 0, sizeof(vis));
    l[s][s] = 0;
    for (int i = 1; i <= n; i++)
    {
        int x = 0;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && (!x || l[s][j] < l[s][x]))
                x = j;
        vis[x] = 1;
        for (int j = 1; j <= n; j++)
            l[s][j] = min(l[s][j], l[s][x] + l[x][j]);
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("T296830.in", "r", stdin);
    freopen("T296830.out", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &q, &st);
    memset(l, 0x3F, sizeof(l));
    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        l[x][y] = l[y][x] = 1;
    }
    st1 = st2 = st;
    for (int i = 0; i < q; i++)
    {
        set<int> tmp;
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++)
        {
            int x;
            scanf("%d", &x);
            tmp.insert(x);
        }
        int MinIndex = 0,
            MinValue = INF,
            MaxIndex = 0,
            MaxValue = -INF;
        if (l[st1][st1] != 0)
            dijkstra(st1);
        if (l[st2][st2] != 0)
            dijkstra(st2);
        for (auto i : tmp)
        {
            if (l[st1][i] < MinValue)
            {
                MinValue = l[st1][i];
                MinIndex = i;
            }
            if (l[st2][i] > MaxValue)
            {
                MaxValue = l[st2][i];
                MaxIndex = i;
            }
        }
        ans1 += MinValue;
        ans2 += MaxValue;
        st1 = MinIndex;
        st2 = MaxIndex;
#ifndef ONLINE_JUDGE
        cout << st1 << " " << st2 << "  " << ans1 << " " << ans2 << endl;
#endif
        swap(ans1, ans2);
        swap(st1, st2);
    }
    if (q % 2 == 0)
        swap(ans1, ans2);
    cout << ans1 << " " << ans2 << endl;
    return 0;
}