#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, in[N], Order[N];
bool Visited[N];
vector<int> g[N];
void init()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        in[v]++;
    }
}
bool TopoSort()
{
    queue<int> q;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (in[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        cnt++;
        Order[cnt] = k;
        for (int i = 0; i < g[k].size(); i++)
        {
            in[g[k][i]]--;
            if (in[g[k][i]] == 0)
                q.push(g[k][i]);
        }
    }
    return cnt == n;
}
int main()
{
    init();
    if (TopoSort())
    {
        for (int i = 1; i <= n; i++)
            cout << Order[i] << " ";
        cout << endl;
    }
    else
        cout << "-1" << endl;
    return 0;
}
