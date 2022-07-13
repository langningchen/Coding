#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, f[N][2], z[N], p[N];
vector<int> son[N];
void dfs(int u)
{
    f[u][1] = z[u];
    f[u][0] = 0;
    for (int i = 0; i < son[u].size(); i++)
    {
        int v = son[u][i];
        dfs(v);
        f[u][1] += f[v][0];
        f[u][0] += max(f[v][0], f[v][1]);
    }
}
int main()
{
    freopen("oedipus.in", "r", stdin);
    freopen("oedipus.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> z[i];
    for (int i = 1; i <= n - 1; i++)
    {
        int v, u;
        cin >> v >> u;
        p[v] = u;
        son[u].push_back(v);
    }
    int rt = 0;
    for (int i = 1; i <= n; i++)
        if (!p[i])
        {
            rt = i;
            break;
        }
    dfs(rt);
    cout << max(f[rt][0], f[rt][1]) << endl;
    return 0;
}
