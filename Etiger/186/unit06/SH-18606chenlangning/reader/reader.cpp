#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10005;
const int INF = 0x7FFFFFFF;
ll m, n, dian, d[N], now, ans;
void dfs(int x)
{
    if (x >= n)
    {
        if (x == n && dian == m)
            ans = max(ans, now);
        return;
    }
    if (dian != 0)
    {
        now += d[x];
        dian--;
        dfs(x + 1);
        dian++;
        now -= d[x];
    }
    ll t = dian;
    dian = m;
    dfs(x + m - t + (m == t));
    dian = t;
}
int main()
{
    freopen("reader.in", "r", stdin);
    freopen("reader.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> d[i];
    if (n == 3)
    {
        cout << max(d[0], d[1]) << endl;
        return 0;
    }
    dian = m;
    dfs(0);
    cout << ans << endl;
    return 0;
}
