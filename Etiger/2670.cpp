#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll N = 1000005;
ll n, h[N], x[N], c[N], f[N];
ll g[N], t[N], Q[N];
ll Y(ll i)
{
    return f[i] + g[i];
}
ld X(ll j, ll k)
{
    return 1.0 * (Y(j) - Y(k)) / (t[j] - t[k]);
}
int main()
{
    freopen("dorm3.in", "r", stdin);
    freopen("dorm3.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i <= n; i++)
    {
        cin >> h[i] >> x[i] >> c[i];
        t[i] = t[i - 1] + x[i];
        g[i] = g[i - 1] + h[i] * x[i];
    }
    ll l = 0, r = 0;
    for (ll i = 1; i <= n; i++)
    {
        while (l < r && X(Q[l + 1], Q[l]) < h[i])
            l++;
        ll j = Q[l];
        f[i] = f[j] + h[i] * (t[i] - t[j]) - g[i] + g[j] + c[i];
        while (l < r && X(Q[r], Q[r - 1]) > X(i, Q[r]))
            r--;
        Q[++r] = i;
    }
    cout << f[n] << endl;
    return 0;
}
