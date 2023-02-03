#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int INF = 0x7FFF'FFFF;
int d[N], sum[N];
int main()
{
    freopen("watersupply.in", "r", stdin);
    freopen("watersupply.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> d[i];
        d[i] += d[i - 1];
        sum[i] = sum[i - 1] + d[i];
    }
    int ans = INF;
    for (int i = 1; i <= n; i++)
    {
        int p = 8000 * d[i] + 2000 * (sum[n] - sum[i] - (n - i) * d[i]);
        ans = min(ans, p);
    }
    cout << ans << endl;
    return 0;
}
