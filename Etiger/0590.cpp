#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7FFF'FFFF;
const int N = 2505;
int n, p, m, d[N];
vector<int> to[N];
vector<int> w[N];
int BellmanFord()
{
    fill(d, d + n + 1, INF);
    d[1] = 0;
    for (long long k = 1; k <= n - 1; k++)
    {
        for (long long u = 1; u <= n; u++)
        {
            for (long long i = 0; i < to[u].size(); i++)
            {
                long long v = to[u][i];
                long long cost = w[u][i];
                d[v] = min((long long)d[v], d[u] + cost);
            }
        }
    }
    for (long long u = 1; u <= n; u++)
    {
        for (long long i = 0; i < to[u].size(); i++)
        {
            long long v = to[u][i];
            long long cost = w[u][i];
            if (d[v] > d[u] + cost)
                return 1;
        }
    }
    return 0;
}
int main()
{
    freopen("timemachine.in", "r", stdin);
    freopen("timemachine.out", "w", stdout);
    cin >> n >> p >> m;
    for (long long i = 0; i < p; i++)
    {
        long long u, v, cost;
        cin >> u >> v >> cost;
        to[u].push_back(v);
        w[u].push_back(-cost);
    }
    for (long long i = 0; i < m; i++)
    {
        long long u, v, cost;
        cin >> u >> v >> cost;
        to[u].push_back(v);
        w[u].push_back(cost);
        to[v].push_back(u);
        w[v].push_back(cost);
    }
    long long ans = BellmanFord();
    if (ans)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}
