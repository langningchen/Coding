#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFF'FFFF;
ll n, a, b, q[N], x[N], f[N];
int main()
{
    freopen("dog.in", "r", stdin);
    freopen("dog.out", "w", stdout);
    cin >> n >> a >> b;
    for (ll i = 1; i <= n; i++)
        cin >> x[i];
    f[0] = 0;
    ll l = 0, r = 0;
    for (ll i = 1; i <= n; i++)
    {
        ll L = i - b - 1;
        L = max(L, 0LL);
        ll R = i - a - 1;
        f[i] = INF;
        if (R < 0)
            continue;
        while (l < r && q[l] < L)
            l++;
        while (l < r && f[q[r - 1]] > f[R])
            r--;
        q[r++] = R;
        if (f[q[l]] == INF)
            continue;
        f[i] = f[q[l]] + x[i];
    }
    if (f[n] == INF)
        cout << -1 << endl;
    else
        cout << f[n] << endl;
    return 0;
}
