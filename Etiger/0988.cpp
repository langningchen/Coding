#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFFFFF;
ll n, m, dst[N], vst[N];
bool ok[N];
vector<ll> to[N];
vector<ll> w[N];
ll in[N], cnt[N];
bool spfa()
{
    fill(dst, dst + n + 9, INF);
    queue<int> q;
    dst[n] = 0;
    in[n] = 1;
    cnt[n] = 1;
    q.push(n);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        in[u] = 0;
        for (int i = 0, v; i < to[u].size(); i++)
            if (dst[v = to[u][i]] > dst[u] + w[u][i])
            {
                dst[v] = dst[u] + w[u][i];
                if (!in[v])
                    q.push(v), in[v] = 1, cnt[v]++;
                if (cnt[v] == n)
                    return -1;
            }
    }
    return 0;
}
int main()
{
    freopen("greatwall2.in", "r", stdin);
    freopen("greatwall2.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a > b)
            swap(a, b);
        to[b].push_back(a - 1);
        w[b].push_back(-c);
    }
    for (int i = 1; i <= n; i++)
    {
        to[i].push_back(i - 1);
        w[i].push_back(0);
        to[i - 1].push_back(i);
        w[i - 1].push_back(1);
    }
    spfa();
    cout << -dst[0] << endl;
    return 0;
}
