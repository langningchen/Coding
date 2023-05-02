#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 65;
const ll M = 32005;
ll n, m, f[M];
pair<ll, ll> Main[N];
vector<pair<ll, ll>> Second[N];
int main()
{
    freopen("budget.in", "r", stdin);
    freopen("budget.out", "w", stdout);
    scanf("%lld%lld", &m, &n);
    for (ll i = 1; i <= n; i++)
    {
        ll v, w, q;
        scanf("%lld%lld%lld", &v, &w, &q);
        if (q == 0)
            Main[i] = {v, v * w};
        else
            Second[q].push_back({v, v * w});
    }
    for (ll i = 1; i <= n; i++)
        for (ll j = m; j >= 0; j--)
            for (ll k = 0; k < (1 << Second[i].size()); k++)
            {
                ll v = Main[i].first;
                ll w = Main[i].second;
                for (ll u = 0; u < Second[i].size(); u++)
                    if (k >> u & 1)
                    {
                        v += Second[i][u].first;
                        w += Second[i][u].second;
                    }
                if (j >= v)
                    f[j] = max(f[j], f[j - v] + w);
            }
    printf("%lld\n", f[m]);
    return 0;
}
