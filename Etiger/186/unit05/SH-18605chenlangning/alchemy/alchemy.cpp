#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
const ll INF = 0x7FFFFFFFFFFFFFFF;
ll n, k, a[N], f[N], ans = INF, Size[N];
set<ll> Need;
ll find(ll x)
{
    return (x == f[x] ? x : f[x] = find(f[x]));
}
void u(ll x, ll y)
{
    f[find(x)] = f[find(y)];
}
int main()
{
    freopen("alchemy.in", "r", stdin);
    freopen("alchemy.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        f[i] = i;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        ll l, m;
        cin >> l >> m;
        l--;
        for (int j = 0; j < m; j++)
        {
            ll t;
            cin >> t;
            t--;
            if (l == n - 1)
                Need.insert(t);
            else
                u(t, l);
        }
    }
    for (int i = 0; i < n; i++)
        if (Need.count(find(i)))
            Size[find(i)] += a[i];
    for (set<ll>::iterator sit = Need.begin(); sit != Need.end(); sit++)
        ans = min(ans, Size[*sit]);
    cout << ans << endl;
    return 0;
}