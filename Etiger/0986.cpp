#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50050;
const int INF = 0x7FFFFFF;
ll n, m, dst[N], vst[N];
bool ok[N];
vector<ll> to[N];
vector<ll> w[N];
struct Node
{
    ll c, u;
    bool operator<(const Node &a) const
    {
        return c > a.c;
    }
};
void dijkstra()
{
    fill(dst, dst + n + 9, INF);
    priority_queue<Node> q;
    q.push((Node){0, 1});
    dst[1] = 0;
    while (!q.empty())
    {
        ll u = q.top().u;
        q.pop();
        if (ok[u])
            continue;
        ok[u] = 1;
        for (ll i = 0; i < to[u].size(); i++)
        {
            ll v = to[u][i];
            if (!ok[v] && dst[v] > dst[u] + w[u][i])
            {
                dst[v] = dst[u] + w[u][i];
                q.push((Node){dst[v], v});
            }
        }
    }
}
int main()
{
    freopen("bonus.in", "r", stdin);
    freopen("bonus.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        to[a].push_back(b);
        w[a].push_back(c);
    }
    dijkstra();
    cout << dst[2] << endl;
    return 0;
}
