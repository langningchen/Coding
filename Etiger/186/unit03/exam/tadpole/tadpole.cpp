#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll x, y, t = 1, d = 1, ans;
int main()
{
    freopen("tadpole.in", "r", stdin);
    freopen("tadpole.out", "w", stdout);
    cin >> x >> y;
    while (1)
    {
        if (x < y && x + t * d >= y)
        {
            ans += y - x;
            break;
        }
        else if (x > y && x + t * d <= y)
        {
            ans += x - y;
            break;
        }
        ans += t * 2;
        t *= 2;
        d = (d == 1 ? -1 : 1);
    }
    cout << ans << endl;
    return 0;
}