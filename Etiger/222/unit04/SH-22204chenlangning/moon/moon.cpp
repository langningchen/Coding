#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
double l, c, u, p, n;
int main()
{
    freopen("moon.in", "r", stdin);
    freopen("moon.out", "w", stdout);
    cin >> l >> c >> u >> p >> n;
    if (n == 0)
    {
        if (c * u > l)
            cout << -1 << endl;
        else
            cout << fixed << setprecision(2) << l / u * p << endl;
    }
    else
        cout << -1 << endl;
    return 0;
}