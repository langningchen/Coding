#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int x[100000], m, n, cnt, ans;
bool OK(ll len)
{
    ll cnt = 0;
    for (ll i = 0; i < n; i++)
    {
        cnt += x[i] / len;
        if (cnt >= m)
            return 1;
    }
    return 0;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    ll l = 1;
    ll r = *max_element(x, x + n);
    ll ans = 0;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (OK(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    cout << ans << endl;
    return 0;
}
