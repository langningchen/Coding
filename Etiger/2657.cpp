#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll n, m, clr[N];
vector<ll> p[N];
void solve()
{
    for (ll i = 1; i <= n; i++)
        p[clr[i]].push_back(i);
    for (ll i = 1; i <= m; i++)
    {
        ll x, y, z;
        cin >> x >> y >> z;
        ll uby = upper_bound(p[z].begin(), p[z].end(), y) - p[z].begin();
        ll lbx = lower_bound(p[z].begin(), p[z].end(), x) - p[z].begin();
        ll ans = uby - lbx;
        cout << ans << " ";
    }
    cout << endl;
}
int main()
{
    freopen("chameleon.in", "r", stdin);
    freopen("chameleon.out", "w", stdout);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> clr[i];
    solve();
    return 0;
}
