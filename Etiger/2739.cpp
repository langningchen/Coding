#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 400005;
bool vst[N];
vector<int> to[N];
void add(int u, int v)
{
    to[u].push_back(v);
    to[v].push_back(u);
}
void dfs(int u)
{
    vst[u] = 1;
    for (unsigned int i = 0; i < to[u].size(); i++)
    {
        int v = to[u][i];
        if (!vst[v])
            dfs(v);
    }
}
int main()
{
    freopen("seeds.in", "r", stdin);
    freopen("seeds.out", "w", stdout);
    int r, c, q;
    cin >> r >> c >> q;
    for (int i = 1; i <= q; i++)
    {
        int x, y;
        cin >> x >> y;
        add(x, r + y);
    }
    int nV = r + c;
    int cnt = 0;
    for (int u = 1; u <= nV; u++)
        if (!vst[u])
        {
            dfs(u);
            cnt++;
        }
    cout << cnt - 1 << endl;
    return 0;
}