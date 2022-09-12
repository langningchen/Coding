#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int T, n, in[N], d[N], cnt[N];
vector<int> to[N], w[N];
int spfa()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
    {
        q.push(i);
        in[i] = cnt[i] = 1;
    }
    while (!q.empty())
    {
        int v, u = q.front();
        q.pop();
        in[u] = 0;
        for (int i = 0; i < to[u].size(); i++)
        {
            v = to[u][i];
            if (d[v] > d[u] + w[u][i])
            {
                d[v] = d[u] + w[u][i];
                if (!in[v])
                {
                    in[v] = 1;
                    cnt[v]++;
                    q.push(v);
                }
                if (cnt[v] > n)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
void addE(int a, int b, int v)
{
    to[a].push_back(b);
    w[a].push_back(v);
}
int main()
{
    freopen("inequality.in", "r", stdin);
    freopen("inequality.out", "w", stdout);
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        cin >> n;
        for (int i = 0; i < 26; i++)
        {
            to[i].clear();
            w[i].clear();
        }
        for (int i = 1; i <= n; i++)
        {
            char x, y, ch;
            int c;
            cin >> x >> ch >> y >> ch >> ch >> c;
            addE(y - 'a', x - 'a', c);
        }
        if (spfa())
        {
            cout << "impossible" << endl;
        }
        else
        {
            cout << "possible" << endl;
        }
    }
    return 0;
}
