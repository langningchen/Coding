#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, m, x[N], f[100][N];
int main()
{
    freopen("god8.in", "r", stdin);
    freopen("god8.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++)
        f[1][i] = x[i] + max(0, f[1][i - 1]);
    for (int p = 2; p <= m; p++)
    {
        int MAX = 0;
        for (int i = 1; i <= n - m + p; i++)
        {
            MAX = max(MAX, f[p & 1 ^ 1][i - 1]);
            f[p & 1][i] = x[i] + max(MAX, f[p & 1][i - 1]);
        }
    }
    cout << max(0, *max_element(f[m & 1] + 1, f[m & 1] + 1 + n)) << endl;
    return 0;
}
