#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 50005;
const int M = 100005;
ll n, m, q[N], x[M], ans[M];
struct Line
{
    ll b, k;
} lines[N];
ld X(ll u, ll v)
{
    return -(ld)(lines[u].b - lines[v].b) / (lines[u].k - lines[v].k);
}
int main()
{
    freopen("lines.in", "r", stdin);
    freopen("lines.out", "w", stdout);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> lines[i].b;
    for (ll i = 1; i <= n; i++)
        cin >> lines[i].k;
    for (ll i = 1; i <= m; i++)
        cin >> x[i];
    ll l = 1, r = 1;
    for (ll i = 1; i <= n; i++)
    {
        while (r - l >= 2 && X(i, q[r - 1]) < X(q[r - 1], q[r - 2]))
            r--;
        q[r++] = i;
    }
    for (ll i = 1; i <= m; i++)
    {
        while (r - l >= 2 && X(q[l], q[l + 1]) < x[i])
            l++;
        ll j = q[l];
        ans[i] = lines[j].b + lines[j].k * x[i];
    }
    for (ll i = 1; i <= m; i++)
        cout << ans[i] << " ";
    return 0;
}