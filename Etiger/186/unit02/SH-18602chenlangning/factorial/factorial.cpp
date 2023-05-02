#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1000000009;
ll a, aa = 1, b, bb = 1, ans;
int main()
{
    freopen("factorial.in", "r", stdin);
    freopen("factorial.out", "w", stdout);
    cin >> a >> b;
    for (ll i = 2; i <= a; i++)
        aa = (aa * i) % MOD;
    for (ll i = 2; i <= b; i++)
        bb = (bb * i) % MOD;
    ans = (bb - aa) % MOD;
    if (ans < 0)
        ans += MOD;
    cout << ans << endl;
    return 0;
}
