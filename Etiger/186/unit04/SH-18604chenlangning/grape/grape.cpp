#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
const int INF = 0x7FFFFFFF;
int n;
vector<int> to[N];
map<pair<int, int>, int> EdgeList;
void dfs(int x, int y)
{
    ll ans = 0;
    for (vector<int>::iterator vit = to[y].begin(); vit != to[y].end(); vit++)
    {
        if (*vit == x)
            continue;
        if (EdgeList[make_pair(min(y, *vit), max(y, *vit))] == 0)
            dfs(y, *vit);
        ans += EdgeList[make_pair(min(y, *vit), max(y, *vit))];
    }
    EdgeList[make_pair(min(x, y), max(x, y))] = ans + 1;
}
int main()
{
    freopen("grape.in", "r", stdin);
    freopen("grape.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        to[a].push_back(b);
        to[b].push_back(a);
    }
    dfs(1, to[1][0]);
    double Delta = n;
    int ans[3];
    int x[2], y[2];
    double Average = n / 3.0;
    for (map<pair<int, int>, int>::iterator mit = EdgeList.begin(); mit != EdgeList.end(); mit++)
        (mit->second) = min((int)(mit->second), (int)(n - (mit->second)));
    for (int i = 0; i < 2; i++)
    {
        Delta = n;
        for (map<pair<int, int>, int>::iterator mit = EdgeList.begin(); mit != EdgeList.end(); mit++)
            if (abs(Average - (double)(mit->second)) < Delta)
            {
                Delta = abs(Average - (double)(mit->second));
                ans[i] = mit->second;
                x[i] = mit->first.first;
                y[i] = mit->first.second;
            }
        EdgeList[make_pair(x[i], y[i])] = n;
    }
    ans[2] = n - ans[0] - ans[1];
    sort(ans, ans + 3);
    cout << ans[2] - ans[0] << endl;
    return 0;
}