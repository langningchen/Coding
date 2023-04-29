#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, m, W, id[N], w[N], b[N], sW[N], sB[N], f[N];
struct item
{
    int w, b;
};
vector<item> g[N];
int root(int x)
{
    return id[x] == x ? x : id[x] = root(id[x]);
}
void unite(int x, int y)
{
    id[root(x)] = root(y);
}
int main()
{
    freopen("party.in", "r", stdin);
    freopen("party.out", "w", stdout);
    cin >> n >> m >> W;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        id[i] = i;
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        unite(x, y);
    }
    for (int i = 1; i <= n; i++)
    {
        sW[root(i)] += w[i];
        sB[root(i)] += b[i];
    }
    for (int i = 1; i <= n; i++)
        g[root(i)].push_back((item){w[i], b[i]});
    for (int i = 1; i <= n; i++)
        if (id[i] == i)
            g[i].push_back((item){sW[i], sB[i]});
    for (int i = 1; i <= n; i++)
        if (id[i] == i)
            for (int j = W; j >= 0; j--)
                for (int k = 0; k < g[i].size(); k++)
                    if (j >= g[i][k].w)
                        f[j] = max(f[j], f[j - g[i][k].w] + g[i][k].b);
    cout << f[W] << endl;
    return 0;
}