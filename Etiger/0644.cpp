#include <bits/stdc++.h>
using namespace std;
const int N = 50005;
int n, m, a, b, c, x, BiG, vst[N];
vector<int> to[N];
void dfs(int u, int color)
{
    if (!BiG)
        return;
    vst[u] = color;
    for (int i = 0; i < to[u].size(); i++)
        if (!vst[to[u][i]])
            dfs(to[u][i], 3 - color);
        else if (vst[to[u][i]] == color)
            BiG = 0;
}
int main()
{
    freopen("criminal5.in", "r", stdin);
    freopen("criminal5.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        to[a].push_back(b);
        to[b].push_back(a);
    }
    fill(vst, vst + n + 1, 0);
    BiG = 1;
    for (int i = 1; i <= n && BiG; i++)
        if (!vst[i])
            dfs(i, 1);
    if (BiG)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
