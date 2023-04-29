#include <bits/stdc++.h>
using namespace std;
const int MAXN = 60005;
int n, hd[MAXN], to[MAXN * 2], nxt[MAXN * 2], id, tot, s[MAXN], e[MAXN], dep[MAXN];
void link(int father, int son)
{
    ++tot;
    to[tot] = son;
    nxt[tot] = hd[father];
    hd[father] = tot;
}
void dfs(int x, int f)
{
    dep[x] = dep[f] + 1;
    s[x] = ++id;
    for (int i = hd[x]; i; i = nxt[i])
        if (to[i] != f)
            dfs(to[i], x);
    e[x] = id;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        link(x, y);
        link(y, x);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d %d\n", e[i] - s[i] + 1, dep[i]);
    return 0;
}
