#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dir = 1, by = 1;
int main()
{
    freopen("tadpole.in", "r", stdin);
    freopen("tadpole.out", "w", stdout);
    ll x, y;
    cin >> x >> y;
    ll ans = 0;
    while (true)
    {
        if ((dir == 1 && x <= y && y <= x + by) ||
            (dir == -1 && x - by <= y && y <= x))
        {
            ans += abs(y - x);
            cout << ans << endl;
            break;
        }
        else
        {
            ans += by * 2;
            by *= 2;
            dir *= -1;
        }
    }
    return 0;
}