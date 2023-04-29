#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, x[N], f[N];
int main()
{
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
    while (cin >> x[n + 1])
        n++;
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (x[j] < x[i])
                f[i] = max(f[i], f[j] + 1);
    }
    int ans = *max_element(f + 1, f + 1 + n);
    cout << ans << endl;
    return 0;
}
