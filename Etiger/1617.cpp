#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("metis.in", "r", stdin);
    freopen("metis.out", "w", stdout);
    int q, k, m, ans;
    cin >> q >> k >> m;
    if (q + k * m < 100)
        ans = -1;
    else if (q + m >= 100)
        ans = 0;
    else if (k == 1)
        ans = 0;
    else
        ans = ceil(1.0 * (100 - q - m) / (k - 1));
    cout << ans << endl;
    return 0;
}
