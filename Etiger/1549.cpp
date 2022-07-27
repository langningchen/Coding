#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const int N = 100005;
ld n, p, g[N], h[N], a[N];
int main()
{
    freopen("ddr2.in", "r", stdin);
    freopen("ddr2.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> p;
        g[i] = p * (g[i - 1] + 1);
        h[i] = p * (h[i - 1] + 2 * g[i - 1] + 1);
        a[i] = p * (3 * h[i - 1] + 3 * g[i - 1] + 1);
    }
    ld sum = 0;
    for (int i = 1; i <= n; i++)
        sum += a[i];
    cout << fixed << setprecision(1) << sum << endl;
    return 0;
}