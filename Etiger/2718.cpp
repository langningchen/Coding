#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
const ll M = 10000005;
ll n, m, s[N], p[N], cnt[M];
int main()
{
    freopen("share.in", "r", stdin);
    freopen("share.out", "w", stdout);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> p[i];
    for (ll i = 1; i <= n; i++)
    {
        s[i] = s[i - 1] + p[i];
        s[i] = (s[i] % m + m) % m;
        cnt[s[i]]++;
    }
    cnt[0]++;
    ll ans = 0;
    for (ll r = 0; r < m; r++)
    {
        if (cnt[r] <= 1)
            continue;
        ans += cnt[r] * (cnt[r] - 1) / 2;
    }
    cout << ans << endl;
    return 0;
}