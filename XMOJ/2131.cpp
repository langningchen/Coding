#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
unsigned int n, m, ve[N], vl[N], In[N], Out[N];
struct EDGE
{
    unsigned int v, w;
};
vector<EDGE> G[N];
queue<int> q;
stack<int> topOrder;
int main()
{
    cin >> n >> m;
    for (unsigned int i = 0; i < m; i++)
    {
        unsigned int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        G[u].push_back((EDGE){v, w});
        In[v]++;
        Out[u]++;
    }
    for (unsigned int i = 0; i < n; i++)
        if (Out[i] == 0)
        {
            G[i].push_back((EDGE){n, 0});
            In[n]++;
            Out[i]++;
        }
    n++;
    memset(ve, 0, sizeof(ve));
    for (unsigned int i = 0; i < n; i++)
        if (In[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topOrder.push(u);
        for (unsigned int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i].v;
            In[v]--;
            if (In[v] == 0)
                q.push(v);
            if (ve[u] + G[u][i].w > ve[v])
                ve[v] = ve[u] + G[u][i].w;
        }
    }
    fill(vl, vl + n, ve[n - 1]);
    while (!topOrder.empty())
    {
        int u = topOrder.top();
        topOrder.pop();
        for (unsigned int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i].v;
            if (vl[v] - G[u][i].w < vl[u])
                vl[u] = vl[v] - G[u][i].w;
        }
    }
    cout << ve[n - 1] << endl;
    for (unsigned int u = 0; u < n - 1; u++)
        cout << ve[u] << " " << vl[u] << endl;
    return 0;
}
