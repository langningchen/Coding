#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, x[N], f[N];
int main()
{
    freopen("subsequence.in", "r", stdin);
    freopen("subsequence.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    f[0] = 0;
    for (int i = 1; i <= n; i++)
        f[i] = max(f[i - 1], 0) + x[i];
    cout << *max_element(f + 1, f + n + 10) << " " << max_element(f + 1, f + n + 1) - f << endl;
    return 0;
}
