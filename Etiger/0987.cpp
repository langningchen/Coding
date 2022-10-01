#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7FFFFFF;
const int N = 1005;
int n, p, q, dst[N], vst[N], cnt[N], in[N];
vector<int> to[N];
vector<int> w[N];
bool spfa()
{
    queue<int> q;
    dst[1] = 0;
    in[1] = 1;
    cnt[1] = 1;
    q.push(1);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        in[u] = 0;
        for (int i = 0, v; i < to[u].size(); i++)
        {
            if (dst[v = to[u][i]] > dst[u] + w[u][i])
            {
                dst[v] = dst[u] + w[u][i];
                if (!in[v])
                    q.push(v), in[v] = 1, cnt[v]++;
                if (cnt[v] == n)
                    return 1;
            }
        }
    }
    return 0;
}
int main()
{
    freopen("army.in", "r", stdin);
    freopen("army.out", "w", stdout);
    cin >> n >> p >> q;
    fill(dst, dst + n + 3, INF);
    fill(vst, vst + n + 3, false);
    for (int i = 0; i < p; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a > b)
            swap(a, b);
        to[a].push_back(b);
        w[a].push_back(c);
    }
    for (int i = 0; i < q; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a > b)
            swap(a, b);
        to[b].push_back(a);
        w[b].push_back(-c);
    }
    if (spfa())
    {
        cout << "impossible" << endl;
    }
    else if (dst[n] != INF)
    {
        cout << dst[n] << endl;
    }
    else
    {
        cout << "infinity" << endl;
    }
    return 0;
}
