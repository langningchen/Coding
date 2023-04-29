#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
ll n, m, id[N], cnt[N];
struct edge
{
    ll u, v;
} E[N];
ll root(ll x)
{
    return id[x] == x ? x : id[x] = root(id[x]);
}
int main()
{
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
    cin >> n;
    for (ll u = 1; u <= n; u++)
        id[u] = u;
    for (int i = 1; i <= n - 1; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        if (c)
            E[++m] = (edge){a, b};
        else
            id[root(a)] = root(b);
    }
    for (ll u = 1; u <= n; u++)
        cnt[root(u)]++;
    ll sum = 0;
    for (ll i = 1; i <= n; i++)
    {
        ll ru = root(E[i].u);
        ll rv = root(E[i].v);
        sum = max(sum, cnt[ru] * cnt[rv]);
    }
    for (ll u = 1; u <= n; u++)
        sum += cnt[u] * (cnt[u] - 1) / 2;
    ll ans = n * (n - 1) / 2 - sum;
    cout << ans << endl;
    return 0;
}