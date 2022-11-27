#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, L, bst[N], q[N], h[N], s[N], f[N];
void RMLwL()
{
    ll l = 0, r = 0;
    for (ll i = 1; i <= n; i++)
    {
        while (l < r && i - q[l] >= L)
            l++;
        while (l < r && h[i] <= h[q[r - 1]])
            r--;
        q[r++] = i;
        bst[i] = h[q[l]];
    }
}
int main()
{
    freopen("flood.in", "r", stdin);
    freopen("flood.out", "w", stdout);
    cin >> n >> L;
    for (ll i = 1; i <= n; i++)
        cin >> h[i];
    for (ll i = 1; i <= n; i++)
        s[i] = s[i - 1] + h[i];
    RMLwL();
    for (ll i = 1; i <= n; i++)
    {
        f[i] = f[i - 1] + h[i];
        if (i < L)
            continue;
        f[i] = min(f[i], f[i - L] + s[i] - s[i - L] - bst[i]);
    }
    cout << f[n] << endl;
    return 0;
}
