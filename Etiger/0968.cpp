#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, h[N];
int main()
{
    freopen("banner.in", "r", stdin);
    freopen("banner.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> h[i];
    ll l = 1, r = n, ans = 0;
    while (l < r)
    {
        ll height = min(h[l], h[r]);
        ll width = r - l + 1;
        ll area = height * width;
        ans = max(ans, area);
        if (h[l] < h[r])
            l++;
        else
            r--;
    }
    cout << ans << endl;
    return 0;
}
