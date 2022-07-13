#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 500009;
ll a[N], d[N], n, p, x, y, z;
int main()
{
    cin >> n >> p;
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    for (ll i = 1; i <= n; i++)
        d[i] = a[i] - a[i - 1];
    for (ll i = 1; i <= p; i++)
    {
        cin >> x >> y >> z;
        if (x <= y)
        {
            d[x] += z;
            d[y + 1] -= z;
        }
        else
        {
            d[y] += z;
            d[x + 1] -= z;
        }
    }
    for (ll i = 1; i <= n; i++)
        a[i] = a[i - 1] + d[i];
    cout << *min_element(a + 1, a + 1 + n) << endl;
    return 0;
}
