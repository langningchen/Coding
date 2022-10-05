#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
ll n, l, v, q, t, a[N], sum[N];
int main()
{
    freopen("snail.in", "r", stdin);
    freopen("snail.out", "w", stdout);
    cin >> n >> l >> v;
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    sum[0] = l;
    sort(a, a + n);
    reverse(a, a + n);
    for (ll i = 0; i < n; i++)
        sum[i + 1] = sum[i] + a[i];
    cin >> q;
    for (ll i = 0; i < q; i++)
    {
        cin >> t;
        ll s = t * v;
        ll ans = upper_bound(sum, sum + n + 1, s) - sum;
        if (ans == n + 1)
            cout << "-1" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}