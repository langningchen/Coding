#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n;
double l, r, x[N];
int main()
{
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    cin >> l >> r;
    cout << abs(upper_bound(x, x + n, r) - lower_bound(x, x + n, l)) << " "
         << abs(lower_bound(x, x + n, r) - upper_bound(x, x + n, l)) << " "
         << abs(lower_bound(x, x + n, r) - lower_bound(x, x + n, l)) << " "
         << abs(upper_bound(x, x + n, r) - upper_bound(x, x + n, l));
    return 0;
}
