#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll L, k, x[N];
ll AC(ll n)
{
    freopen("auto.in", "r", stdin);
    freopen("auto.out", "w", stdout);
    ll nAC = 0;
    ll nLines = 0;
    for (ll i = 1; i <= L; i++)
    {
        nLines += x[i];
        if (nLines < 0)
            nLines = 0;
        if (nLines >= n)
        {
            nAC++;
            nLines = 0;
        }
    }
    return nAC;
}
int main()
{
    cin >> L >> k;
    for (int i = 1; i <= L; i++)
        cin >> x[i];
    ll l = 1;
    ll r = 1e18;
    ll mx = 0;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (AC(mid) >= k)
        {
            mx = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    l = 1;
    r = 1e18;
    ll mn = r;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (AC(mid) <= k)
        {
            mn = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    if (AC(mx) != k || AC(mn) != k)
        cout << -1 << endl;
    else
        cout << mn << " " << mx << endl;
    return 0;
}