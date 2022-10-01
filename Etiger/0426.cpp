#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("sniper.in", "r", stdin);
    freopen("sniper.out", "w", stdout);
    int m, a, b, x[50000], y[50000], ans = 0;
    cin >> m >> a >> b;
    for (int i = 0; i < a; i++)
    {
        cin >> x[i];
    }
    for (int i = 0; i < b; i++)
    {
        cin >> y[i];
    }
    sort(y, y + b);
    for (int i = 0; i < a; i++)
    {
        int ma = m - x[i];
        ans += upper_bound(y, y + b, ma) - y;
    }
    cout << ans;
    return 0;
}
