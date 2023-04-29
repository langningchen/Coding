#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10000005;
const int M = 105;
const int INF = 0x7FFF'FFFF;
ll n, a, b, m, pos[N], f[N], x[N], Move[M], sM[M];
int main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    cin >> n >> a >> b >> m;
    for (int i = 1; i <= m; i++)
        cin >> pos[i];
    sort(pos + 1, pos + 1 + m);
    if (a == b)
    {
        ll ans = 0;
        for (ll i = 1; i <= m; i++)
            if (pos[i] % a == 0)
                ans++;
        cout << ans << endl;
        return 0;
    }
    if (n * (b - a + 1) > 1e7)
    {
        ll GAP = 200;
        pos[0] = 0;
        for (ll i = 1; i <= m; i++)
            if (pos[i] - pos[i - 1] > GAP)
                Move[i] = pos[i] - (pos[i - 1] + GAP);
        for (ll i = 1; i <= m; i++)
            sM[i] = sM[i - 1] + Move[i];
        for (ll i = 1; i <= m; i++)
            pos[i] -= sM[i];
        n = pos[m] + GAP;
    }
    f[0] = 0;
    for (ll i = 1; i <= m; i++)
        x[pos[i]] = 1;
    for (ll i = 1; i <= n + a - 1; i++)
    {
        ll L = i - b;
        L = max(L, 0LL);
        ll R = i - a;
        f[i] = INF;
        for (ll j = L; j <= R; j++)
            if (f[j] != INF)
                f[i] = min(f[i], f[j] + x[i]);
    }
    ll ans = INF;
    for (ll i = n; i <= n + a - 1; i++)
        ans = min(ans, f[i]);
    cout << ans << endl;
    return 0;
}
