#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 25005;
ll a, b, n, m, x[N], y[N], dx[N], dy[N];
int main()
{
    freopen("draw.in", "r", stdin);
    freopen("draw.out", "w", stdout);
    cin >> a >> b >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    for (int i = 1; i <= m; i++)
        cin >> y[i];
    x[n + 1] = a;
    y[m + 1] = b;
    sort(x + 1, x + n + 2);
    sort(y + 1, y + m + 2);
    for (ll i = 1; i <= n + 1; i++)
        dx[i] = x[i] - x[i - 1];
    for (ll i = 1; i <= m + 1; i++)
        dy[i] = y[i] - y[i - 1];
    sort(dx + 1, dx + n + 2);
    sort(dy + 1, dy + m + 2);
    ll ans = dx[1] * m + dy[1] * n;
    ll cX = 1, cY = 1;
    for (ll i = 1; i <= n + m; i++)
    {
        if (cX + 1 <= n + 1 && dx[cX + 1] < dy[cY + 1])
        {
            cX++;
            ans += dx[cX] * (m + 1 - cY);
        }
        else
        {
            cY++;
            ans += dy[cY] * (n + 1 - cX);
        }
    }
    cout << ans << endl;
    return 0;
}