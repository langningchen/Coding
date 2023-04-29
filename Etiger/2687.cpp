#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1000005;
ll n, m, mx, y, ans, c[N];
vector<ll> v;
ll LowBit(ll x)
{
    return x & (-x);
}
void add(ll x, ll y)
{
    while (x <= mx)
    {
        c[x] += y;
        x += LowBit(x);
    }
}
ll psq(ll x)
{
    ll res = 0;
    while (x > 0)
    {
        res += c[x];
        x -= LowBit(x);
    }
    return res;
}
ll search(ll y)
{
    ll l = 1, r = mx, res = mx;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (psq(mid) >= y)
        {
            res = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return res;
}
int main()
{
    freopen("premiere4.in", "r", stdin);
    freopen("premiere4.out", "w", stdout);
    cin >> n >> m;
    mx = n + m;
    for (ll i = 1; i <= n; i++)
        add(i, 1);
    for (ll iQ = 1; iQ <= m; iQ++)
    {
        cin >> y;
        ll cnt = 0;
        ll id = search(y);
        add(id, -1);
        add(n + iQ, 1);
        if (id <= n)
            ans = id;
        else
            ans = v[id - n - 1];
        v.push_back(ans);
        cout << ans << " ";
    }
    return 0;
}
