#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFFFFFF;
ll n, nX, nY, x[N], y[N], sX, sY, cX, cY, ans;
void dfs(ll i)
{
    if (i == n)
    {
        ans = max(ans, sX + sY);
        return;
    }
    if (cX < nX)
    {
        cX++;
        sX += x[i];
        dfs(i + 1);
        sX -= x[i];
        cX--;
    }
    if (cY < nY)
    {
        cY++;
        sY += y[i];
        dfs(i + 1);
        sY -= y[i];
        cY--;
    }
}
int main()
{
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    cin >> n >> nX >> nY;
    for (ll i = 0; i < n; i++)
        cin >> x[i];
    for (ll i = 0; i < n; i++)
        cin >> y[i];
    dfs(0);
    cout << ans << endl;
    return 0;
}
