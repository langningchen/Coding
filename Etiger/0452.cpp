#include <bits/stdc++.h>
using namespace std;
const int N = 1009;
const int INF = 1e9;
int n, a, b, f[N];
int main()
{
    freopen("steps.in", "r", stdin);
    freopen("steps.out", "w", stdout);
    cin >> n >> a >> b;
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = INF;
        if (i >= a)
            f[i] = min(f[i], f[i - a] + 1);
        if (i >= b)
            f[i] = min(f[i], f[i - b] + 1);
    }
    if (f[n] == INF)
        cout << -1 << endl;
    else
        cout << f[n] << endl;
    return 0;
}
