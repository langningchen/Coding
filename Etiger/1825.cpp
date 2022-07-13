#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
vector<int> to[N];
int L, n, q, p[N][20];
void dfs(int u, int fa)
{
    p[u][0] = fa;
    for (int i = 1; i <= L; i++)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = 0; i < to[u].size(); i++)
        if (to[u][i] != fa)
            dfs(to[u][i], u);
}
int LA(int u, int k)
{
    for (int i = 0; i <= L; i++)
        if ((1 << i) & k)
            u = p[u][i];
    return u;
}
int main()
{
    freopen("kancestor.in", "r", stdin);
    freopen("kancestor.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    L = log(n) / log(2) + 1;
    dfs(1, 0);
    long long ans = 0;
    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        int x, k;
        cin >> x >> k;
        ans += LA(x, k);
    }
    cout << ans << endl;
    return 0;
}
