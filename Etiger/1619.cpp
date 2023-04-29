#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, k, m, d[N];
int main()
{
    freopen("habitat.in", "r", stdin);
    freopen("habitat.out", "w", stdout);
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++)
        cin >> d[i];
    sort(d + 1, d + 1 + n);
    int cnt = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (d[i] > k * m)
            break;
        if (d[i] <= m)
        {
            ans++;
            continue;
        }
        if (k > 1)
            cnt += ceil(1.0 * (d[i] - m) / (k - 1));
        if (cnt <= m)
            ans++;
        else
            break;
    }
    cout << ans << endl;
    return 0;
}
