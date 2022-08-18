#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
const int INF = 0x7FFFFFFF;
int n, a[N];
stack<int> LastSupply;
ll cost, mincost = INF;
bool Use[N];
void dfs(int x)
{
    if (x == n + 1)
    {
        if (cost < mincost)
        {
            cout << mincost << endl;
            mincost = cost;
        }
        return;
    }
    if (cost >= mincost)
        return;
    cost += a[x] - a[LastSupply.top()];
    Use[x] = 0;
    dfs(x + 1);
    Use[x] = 0;
    cost -= a[x] - a[LastSupply.top()];
    cost += (a[x] - a[LastSupply.top()]) * 4;
    LastSupply.push(x);
    Use[x] = 1;
    dfs(x + 1);
    Use[x] = 0;
    LastSupply.pop();
    cost -= (a[x] - a[LastSupply.top()]) * 4;
}
int main()
{
    freopen("watersupply.in", "r", stdin);
    freopen("watersupply.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int t;
        cin >> t;
        a[i] = a[i - 1] + t;
    }
    LastSupply.push(1);
    cost = 4 * a[1];
    Use[1] = 1;
    dfs(2);
    cout << mincost * 2000 << endl;
    return 0;
}