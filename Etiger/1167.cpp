#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll a, n, m, k, V;
ll f[N], b[N], v[N];
void bb01(ll b, ll v)
{
    for (ll j = V; j >= b; j--)
        f[j] = max(f[j], f[j - b] + v);
}
void bbINF(ll b, ll v)
{
    for (ll j = b; j <= V; j++)
        f[j] = max(f[j], f[j - b] + v);
}
int main()
{
    cin >> n >> m >> k >> V;
    for (ll i = 1; i <= n + m + k; i++)
        cin >> b[i];
    for (ll i = 1; i <= n + m + k; i++)
        cin >> v[i];
    for (ll i = 1; i <= n; i++)
        bbINF(b[i], v[i]);
    for (ll i = n + 1; i <= n + m; i++)
        bb01(b[i], v[i]);
    for (ll i = n + m + 1; i <= n + m + k; i++)
    {
        cin >> a;
        for (ll k = 1; k <= a; a -= k, k *= 2)
            bb01(k * b[i], k * v[i]);
        if (a)
            bb01(a * b[i], a * v[i]);
    }
    cout << f[V] << endl;
    return 0;
}
