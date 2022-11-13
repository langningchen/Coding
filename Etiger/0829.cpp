#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll N = 100005;
ll n, a[N], q[N], f[N];
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
    freopen("cable.in", "r", stdin);
    freopen("cable.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    lines[0] = (Line){0, 0};
    q[1] = 0;
    ll l = 1, r = 2;
    for (ll i = 1; i <= n; i++)
    {
        while (r - l >= 2 && X(q[l], q[l + 1]) < i)
            l++;
        ll j = q[l];
        f[i] = f[j] + j * (j + 1) / 2 - j * i + a[i] + i * (i - 1) / 2;
        lines[i] = (Line){f[i] + i * (i + 1) / 2, -i};
        while (r - l >= 2 && X(i, q[r - 1]) < X(q[r - 1], q[r - 2]))
            r--;
        q[r++] = i;
    }
    cout << f[n] << endl;
    return 0;
}
