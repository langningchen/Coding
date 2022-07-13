#include <bits/stdc++.h>
using namespace std;
int m, k;
int main()
{
    freopen("blindbox4.in", "r", stdin);
    freopen("blindbox4.out", "w", stdout);
    cin >> m >> k;
    double ans = 0;
    double temp = 1;
    for (int i = 0; i < k; i++)
    {
        temp *= m * 1.0 / (m - i);
        ans += temp;
    }
    cout << fixed << setprecision(6) << ans << endl;
    return 0;
}
