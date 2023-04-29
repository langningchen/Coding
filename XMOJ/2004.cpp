#include <bits/stdc++.h>
using namespace std;
const int N = 500100;
int x, y, n, m, tot, ans, p[N], f1[N], lin[N], f[N][25], d[N], vis[N];
struct
{
    int x, y, next;
} a[N * 2];
void add(int x, int y)
{
    a[++tot].x = x;
    a[tot].y = y;
    a[tot].next = lin[x];
    lin[x] = tot;
}
void bfs(int x)
{
    queue<int> q;
    q.push(1);
    d[1] = 1;
    while (q.size())
    {
        int x = q.front();
        q.pop();
        for (int i = lin[x]; i; i = a[i].next)
        {
            int y = a[i].y;
            if (d[y])
                continue;
            d[y] = d[x] + 1;
            f[y][0] = x;
            for (int j = 1; j <= 23; j++)
            {
                f[y][j] = f[f[y][j - 1]][j - 1];
            }
            q.push(y);
        }
    }
}
int lca(int x, int y)
{
    if (d[x] > d[y])
        swap(x, y);
    for (int i = 23; i >= 0; i--)
    {
        if (d[f[y][i]] >= d[x])
            y = f[y][i];
    }
    if (x == y)
        return x;
    for (int i = 23; i >= 0; i--)
    {
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}
void dfs(int x)
{
    vis[x] = 1;
    for (int i = lin[x]; i; i = a[i].next)
    {
        int y = a[i].y;
        if (vis[y])
            continue;
        dfs(y);
        p[x] += p[y];
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    bfs(1);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        p[x]++, p[y]++;
        p[lca(x, y)] -= 2;
    }
    dfs(1);
    for (int i = 2; i <= n; i++)
    {
        if (!p[i])
            ans += m;
        if (p[i] == 1)
            ans += 1;
    }
    printf("%d\n", ans);
    return 0;
}
