#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1000005;
ll n, c[N], x[N], t[N], g[N], q[N], f[N];
struct Line
{
    ld b, k;
} lines[N];
ld X(ll u, ll v)
{
    return -(ld)(lines[u].b - lines[v].b) / (lines[u].k - lines[v].k);
}
int main()
{
    freopen("dorm2.in", "r", stdin);
    freopen("dorm2.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> c[i];
    for (ll i = 1; i <= n; i++)
        cin >> x[i];
    for (ll i = n; i >= 0; i--)
    {
        t[i] = t[i + 1] + x[i];
        g[i] = g[i + 1] + x[i] * (n - i + 1);
    }
    lines[0] = (Line){g[1] - t[1] * (n + 1), t[1]};
    q[1] = 0;
    ll l = 1, r = 2;
    for (ll i = 1; i <= n; i++)
    {
        while (r - l >= 2 && X(q[l], q[l + 1]) < i)
            l++;
        ll j = q[l];
        f[i] = f[j] + g[j + 1] - g[i] - (t[j + 1] - t[i]) * (n - i + 1) + c[i];
        lines[i] = (Line){f[i] + g[i + 1] - t[i + 1] * (n + 1), t[i + 1]};
        while (r - l >= 2 && X(i, q[r - 1]) < X(q[r - 1], q[r - 2]))
            r--;
        q[r++] = i;
    }
    cout << f[n] << endl;
    return 0;
}
