#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b, h;
int main()
{
    freopen("snail.in", "r", stdin);
    freopen("snail.out", "w", stdout);
    cin >> a >> b >> h;
    if (a <= b && a < h)
        cout << "forever" << endl;
    else
    {
        ll d = a - b;
        ll g = max(h - a, 0ll);
        ll cnt = ceil(g * 1.0 / d);
        cout << cnt * 2 + 1 << endl;
    }
    return 0;
}