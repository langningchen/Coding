#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4000005;
const int INF = 0x7FFFFFFF;
ll m, n, maxt, Move[N], t[N], sM[N], cnt[N], sC[N], sT[N], f[N];
int main()
{
    freopen("bus.in", "r", stdin);
    freopen("bus.out", "w", stdout);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> t[i];
    for (ll i = 1; i <= n; i++)
        ++t[i];
    sort(t + 1, t + 1 + n);
    ll maxt = t[n];
    if (m == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    if (m * maxt > 1e7)
    {
        Move[1] = t[1] - 1;
        for (ll i = 2; i <= n; i++)
            if (t[i] - t[i - 1] > 2 * m)
                Move[i] = t[i] - (t[i - 1] + 2 * m);
        for (ll i = 1; i <= n; i++)
            sM[i] = sM[i - 1] + Move[i];
        for (ll i = 1; i <= n; i++)
            t[i] -= sM[i];
    }
    for (ll i = 1; i <= n; i++)
        cnt[t[i]]++;
    ll END = t[n] + m;
    for (ll T = 1; T <= END; T++)
    {
        sC[T] = sC[T - 1] + cnt[T];
        sT[T] = sT[T - 1] + cnt[T] * T;
    }
    f[0] = 0;
    for (ll T = 1; T <= END; T++)
    {
        ll L = max(T - 2 * m, 0ll);
        ll R = max(T - m, 0ll);
        f[T] = INF;
        for (ll p = L; p <= R; p++)
        {
            ll cost = T * (sC[T] - sC[p]) - (sT[T] - sT[p]);
            f[T] = min(f[T], f[p] + cost);
        }
    }
    ll ans = *min_element(f + t[n], f + END + 1);
    cout << ans << endl;
    return 0;
}
