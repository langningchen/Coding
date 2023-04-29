#include <bits/stdc++.h>
using namespace std;
const int N = 20010;
const int M = 400010;
int n, m, d, p, Head[N], To[M], Weight[M], Next[M], EdgeCount, Distance[22][N], Limit[N], f[1 << 20][21];
bool Visited[N];
void AddEdge(int u, int v, int w)
{
    ++EdgeCount;
    To[EdgeCount] = v;
    Weight[EdgeCount] = w;
    Next[EdgeCount] = Head[u];
    Head[u] = EdgeCount;
}
void Dijkstra(int Start)
{
    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>>
        q;
    memset(Distance[Start], 0x3f, sizeof(Distance[Start]));
    memset(Visited, 0, sizeof(Visited));
    Distance[Start][Start] = 0;
    q.push({0, Start});
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (Visited[x])
            continue;
        Visited[x] = 1;
        for (int i = Head[x]; i; i = Next[i])
            if (Distance[Start][To[i]] > Distance[Start][x] + Weight[i])
            {
                Distance[Start][To[i]] = Distance[Start][x] + Weight[i];
                q.push({Distance[Start][To[i]], To[i]});
            }
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        AddEdge(x, y, z);
        AddEdge(y, x, z);
    }
    for (int i = 1; i <= d + 1; i++)
        Dijkstra(i);
    scanf("%d", &p);
    for (int i = 1; i <= p; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        Limit[y - 1] |= (1 << (x - 2));
    }
    if (d == 0)
    {
        printf("%d\n", Distance[1][n]);
        return 0;
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= d; i++)
        if (!Limit[i])
            f[1 << (i - 1)][i] = Distance[1][i + 1];
    for (int i = 1; i < 1 << d; i++)
        for (int j = 1; j <= d; j++)
            if (i & (1 << (j - 1)))
                for (int k = 1; k <= d; k++)
                    if (!(i & (1 << (k - 1))) && !(~i & Limit[k]))
                        f[i | (1 << (k - 1))][k] =
                            min(f[i | (1 << (k - 1))][k],
                                f[i][j] + Distance[j + 1][k + 1]);
    int ans = 1 << 30;
    for (int i = 1; i <= d; i++)
        ans = min(ans, f[(1 << d) - 1][i] + Distance[i + 1][n]);
    printf("%d\n", ans);
    return 0;
}