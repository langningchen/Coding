/*{*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
const int INF = 0x7FFFFFFF;
int n, m;
set<int> to[N];
set<pair<int, int>> ans;
int main()
{
    freopen("dejavu.in", "r", stdin);
    freopen("dejavu.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0, u, v; i < m; i++)
    {
        cin >> u >> v;
        to[u - 1].insert(v - 1);
        to[v - 1].insert(u - 1);
    }
    for (int x1 = 0; x1 < n; x1++)
    {
        for (int x2 = 0; x2 < n; x2++)
        {
            for (int x3 = 0; x3 < n; x3++)
            {
                if ((to[x1].count(x2) && to[x2].count(x3)) || (!to[x1].count(x2) && !to[x2].count(x3)))
                    ans.insert(make_pair(min(x1, x3), max(x1, x3)));
            }
        }
    }
    cout << ans.size() << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (set<int>::iterator sit = to[i].begin(); sit != to[i].end(); sit++)
    //         for (set<int>::iterator sit2 = to[i].begin(); sit2 != to[i].end(); sit2++)
    //             if (*sit != *sit2)
    //                 ans.insert(make_pair(min(*sit, *sit2), max(*sit, *sit2)));
    //     // ans += to[i].size() * (to[i].size() - 1) / 2;
    // }
    // cout << ans.size() << endl;
    return 0;
}