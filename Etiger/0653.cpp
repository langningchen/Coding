#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ll x, p, m;
    cin >> x >> p >> m;
    ll ans = 1;
    while (p)
    {
        if (p % 2)
            ans = ans * x % m;
        p /= 2;
        x = x * x % m;
    }
    cout << ans << endl;
    return 0;
}