#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll n, x[N], y[N];
ll solve(ll l, ll r)
{
    if (l == r)
        return 0;
    ll mid = (l + r) >> 1;
    ll ret = 0;
    ret += solve(l, mid);
    ret += solve(mid + 1, r);
    ll i = l, j = mid + 1;
    for (ll k = l; k <= r; k++)
        if (i > mid || j <= r && x[i] > x[j])
        {
            ret += mid - i + 1;
            y[k] = x[j++];
        }
        else
            y[k] = x[i++];
    for (ll k = l; k <= r; k++)
        x[k] = y[k];
    return ret;
}
int main()
{
    freopen("reverse.in", "r", stdin);
    freopen("reverse.out", "w", stdout);
    cin >> n;
    for (ll i = 0; i < n; i++)
        cin >> x[i];
    cout << solve(0, n - 1) << endl;
    return 0;
}
