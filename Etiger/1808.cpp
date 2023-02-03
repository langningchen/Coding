#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100'001;
const ll M = 1'000'001;
ll n, k, d[N], cnt[M];
vector<ll> to[N];
vector<ll> w[N];
void dfs(ll u, ll fa)
{
    for (ll i = 0; i < to[u].size(); i++)
    {
        ll v = to[u][i];
        if (v == fa)
            continue;
        d[v] = d[u] ^ w[u][i];
        dfs(v, u);
    }
}
void solve()
{
    dfs(1, 0);
    for (ll u = 1; u <= n; u++)
        cnt[d[u]]++;
    ll ans = 0;
    for (ll u = 1; u <= n; u++)
        ans += cnt[d[u] ^ k];
    if (k == 0)
        ans -= n;
    ans /= 2;
    cout << ans << endl;
}
int main()
{
    // freopen("xor1.in", "r", stdin);
    // freopen("xor1.out", "w", stdout);
    cin >> n >> k;
    for (ll i = 1; i < n; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        a++;
        b++;
        to[a].push_back(b);
        to[b].push_back(a);
        w[a].push_back(c);
        w[b].push_back(c);
    }
    solve();
    return 0;
}
