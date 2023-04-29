#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 60005;
int n, fa[MAXN], hd[MAXN], sons[MAXN], to[MAXN * 2], nxt[MAXN * 2], tot;
void link(int father, int son)
{
    ++tot;
    to[tot] = son;
    nxt[tot] = hd[father];
    hd[father] = tot;
}
void dfs(int x, int f)
{
    sons[f]++;
    for (int i = hd[x]; i; i = nxt[i])
        if (to[i] != f)
            dfs(to[i], x);
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
        printf("%d ", sons[i]);
    printf("\n");
    return 0;
}
