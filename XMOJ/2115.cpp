#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, Answer, in[N], dp[N];
bool Visited[N];
vector<int> g[N];
queue<int> Order;
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
        Order.push(k);
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
    TopoSort();
    while (!Order.empty())
    {
        int k = Order.front();
        Order.pop();
        if (g[k].size() == 0)
        {
            Answer += dp[k];
            continue;
        }
        if (dp[k] == 0)
            dp[k] = 1;
        for (auto i : g[k])
            dp[i] += dp[k];
    }
    cout << Answer << endl;
    return 0;
}
