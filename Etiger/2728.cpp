#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, m, v[N];
int main()
{
    freopen("landing.in", "r", stdin);
    freopen("landing.out", "w", stdout);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
    {
        cin >> v[i];
        v[i] <<= 1;
    }
    for (ll i = 1; i <= m; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        v[a] += c;
        v[b] += c;
    }
    sort(v + 1, v + 1 + n);
    reverse(v + 1, v + 1 + n);
    ll A = 0, B = 0;
    for (ll i = 1; i <= n; i++)
        if (i & 1)
            A += v[i];
        else
            B += v[i];
    cout << ((A - B) >> 1) << endl;
    return 0;
}
