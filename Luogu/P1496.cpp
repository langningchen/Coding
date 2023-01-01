#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20005;
int n, dtop, ctop, a[N], b[N], f[N * 2], d[N * 2];
ll ans, c[N * 2];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
        d[++dtop] = a[i];
        d[++dtop] = b[i];
    }
    sort(d + 1, d + dtop + 1);
    for (int i = 1; i <= dtop; i++)
        if (d[i] != d[i - 1] || i == 1)
            c[++ctop] = d[i];
    for (int i = 1; i <= n; i++)
    {
        int x = lower_bound(c + 1, c + ctop + 1, a[i]) - c;
        int y = lower_bound(c + 1, c + ctop + 1, b[i]) - c;
        for (int j = x; j < y; j++)
            f[j] = 1;
    }
    for (int i = 1; i < ctop; i++)
        if (f[i])
            ans += c[i + 1] - c[i];
    cout << ans << endl;
    return 0;
}