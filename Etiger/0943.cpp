#include <bits/stdc++.h>
using namespace std;
const int N = 20005;
typedef long long ll;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
bool ok[N];
ll n, m, dst[N], x[N];
vector<ll> to[N], w[N];
struct Node
{
    ll c, u;
    bool operator<(const Node &a) const
    {
        return c > a.c;
    }
};
void Dijkstra()
{
    fill(dst, dst + n + 9, INF);
    priority_queue<Node> q;
    dst[1] = 0;
    q.push((Node){0, 1});
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
            if (dst[v] <= dst[u] + w[u][i])
                continue;
            dst[v] = dst[u] + w[u][i];
            q.push((Node){dst[v], v});
        }
    }
}
int main()
{
    freopen("wulin3.in", "r", stdin);
    freopen("wulin3.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        w[a].push_back(c);
        w[b].push_back(c);
        to[a].push_back(b);
        to[b].push_back(a);
    }
    Dijkstra();
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += dst[i] * x[i];
    cout << ans << endl;
    return 0;
}
