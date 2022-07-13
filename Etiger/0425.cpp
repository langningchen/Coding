#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);
    int n;
    double x[10000], l, r;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }
    cin >> l >> r;
    cout << abs(upper_bound(x, x + n, r) - lower_bound(x, x + n, l)) << " " << abs(lower_bound(x, x + n, r) - upper_bound(x, x + n, l)) << " " << abs(lower_bound(x, x + n, r) - lower_bound(x, x + n, l)) << " " << abs(upper_bound(x, x + n, r) - upper_bound(x, x + n, l)); // ���
    return 0;
}
