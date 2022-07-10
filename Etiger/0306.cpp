#include <bits/stdc++.h>
const int N = 305;
int n, f[N], x[N];
using namespace std;
int main()
{
    freopen("tomb.in", "r", stdin);
    freopen("tomb.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    f[0] = 0;
    f[1] = x[1];
    f[2] = max(x[1], x[2]);
    for (int i = 3; i <= n; i++)
        f[i] = max(f[i - 1], f[i - 3] + x[i]);
    cout << f[n] << endl;
    return 0;
}
