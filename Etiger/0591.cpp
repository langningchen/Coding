#include <bits/stdc++.h>
using namespace std;
const int M = 1000005;
const int N = 505;
struct edge
{
    int u, v, w;
};
string gene[N];
edge e[M];
int n, m, id[N];
int root(int u)
{
    return id[u] == u ? u : id[u] = root(id[u]);
}
bool cmp(const edge &a, const edge &b)
{
    return a.w < b.w;
}
void Kruskal()
{
    sort(e, e + m, cmp);
    for (int u = 1; u <= n; u++)
        id[u] = u;
    int ans = 0;
    for (int k = 0; k < m; k++)
    {
        int ru = root(e[k].u);
        int rv = root(e[k].v);
        if (ru == rv)
            continue;
        id[ru] = rv;
        ans += e[k].w;
    }
    cout << ans << endl;
}
int dst(int i, int j)
{
    set<char> s;
    for (int k = 0; k < 5; k++)
    {
        s.insert(gene[i][k]);
        s.insert(gene[j][k]);
    }
    return s.size();
}
int main()
{
    freopen("creator.in", "r", stdin);
    freopen("creator.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> gene[i];
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            e[m].u = i;
            e[m].v = j;
            e[m].w = dst(i, j);
            m++;
        }
    Kruskal();
    return 0;
}
