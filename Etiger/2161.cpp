#include <bits/stdc++.h>

using namespace std;
const int N = 100005;
struct subtree
{
    int L;
    int R;
};

int n, q, dfn[N], s[N], timer;
vector<int> to[N];
subtree T[N];

void dfs(int u, int fa)
{
    T[u].L = dfn[u] = ++timer;
    for (int i = 0; i < to[u].size(); i++)
    {
        if (to[u][i] != fa)
        {
            dfs(to[u][i], u);
        }
    }
    T[u].R = timer;
}
int LSB(int i)
{
    return i & (-i);
}
void add(int d, int num)
{
    for (int i = d; i <= n; i += LSB(i))
    {
        s[i] += num;
    }
}
int pxq(int d)
{
    long long sum = 0;
    for (int i = d; i > 0; i -= LSB(i))
    {
        sum += s[i];
    }
    return sum;
}

int main()
{
    freopen("prodigal.in", "r", stdin);
    freopen("prodigal.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    dfs(1, 0);
    cin >> q;
    for (int i = 1; i <= q; ++i)
    {
        string x;
        cin >> x;
        if (x == "LOSE")
        {
            int u, p;
            cin >> u >> p;
            add(dfn[u], -p);
        }
        else
        {
            int u;
            cin >> u;
            int ans = pxq(T[u].R) - pxq(T[u].L - 1);
            cout << ans << " ";
        }
    }
    return 0;
}
