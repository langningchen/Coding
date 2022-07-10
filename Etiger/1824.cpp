#include <bits/stdc++.h>
using namespace std;
const int N = 1009;
vector<int> to[N];
int n, m;
int tI[N], tO[N], euler[N * 2], timer;
void dfs(int u, int fa)
{
    tI[u] = ++timer;
    euler[timer] = u;
    for (int i = 0; i < to[u].size(); i++)
        if (to[u][i] != fa)
            dfs(to[u][i], u);
    tO[u] = ++timer;
    euler[timer] = u;
}
bool up(int u, int v)
{
    return tI[u] <= tI[v] && tO[v] <= tO[u];
}
int main()
{
    freopen("euler.in", "r", stdin);
    freopen("euler.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    for (int u = 1; u <= n; u++)
        sort(to[u].begin(), to[u].end());
    timer = 0;
    dfs(1, 0);
    for (int i = 1; i < 2 * n; i++)
    {
        cout << euler[i] << " ";
    }
    cout << euler[2 * n] << endl;
    for (int i = 1; i < n; i++)
    {
        cout << tI[i] << " ";
    }
    cout << tI[n] << endl;
    for (int i = 1; i < n; i++)
    {
        cout << tO[i] << " ";
    }
    cout << tO[n] << endl;
    return 0;
}
