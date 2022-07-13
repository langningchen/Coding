#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int MOD = 100000007;
int n, m, L, a[N], b[N], c[N];
void add(ll l, ll r, ll z)
{
    if (b[l] == b[r])
        for (ll i = l; i <= r; i++)
            a[i] = (a[i] + z) % MOD;
    else
    {
        for (ll i = l; b[i] == b[l]; i++)
            a[i] = (a[i] + z) % MOD;
        for (ll i = r; b[i] == b[r]; i--)
            a[i] = (a[i] + z) % MOD;
        for (ll k = b[l] + 1; k <= b[r] - 1; k++)
            c[k] = (c[k] + z) % MOD;
    }
}
int main()
{
    cin >> n >> m;
    L = sqrt(n);
    for (ll i = 1; i <= n; i++)
        b[i] = (i - 1) / L + 1;
    for (ll i = 1; i <= m; i++)
    {
        ll t, x, y, z;
        cin >> t >> x >> y >> z;
        if (t == 1)
            add(x, y, z);
        else
            cout << (a[x] + c[b[x]]) % MOD << endl;
    }
    return 0;
}
