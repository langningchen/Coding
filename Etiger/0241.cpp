#include <bits/stdc++.h>
using namespace std;
const int N = 21;
vector<int> to[N];
int d[N];
void dfs(int u, int fa)
{
    d[u] = d[fa] + 1;
    for (int i = 0; i < to[u].size(); i++)
    {
        if (to[u][i] == fa)
        {
            continue;
        }
        dfs(to[u][i], u);
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        to[a].push_back(b);
        to[b].push_back(a);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
    {
        cout << d[i] << " ";
    }
    cout << endl;
    return 0;
}
