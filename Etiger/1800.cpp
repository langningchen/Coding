#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000009;
ll a, b, ans, f1 = 1, f2 = 1;
int main()
{
    freopen("factorial.in", "r", stdin);
    freopen("factorial.out", "w", stdout);
    cin >> a >> b;
    for (ll i = 2; i <= a; i++)
        f1 = f1 * i % MOD;
    for (ll i = 2; i <= b; i++)
        f2 = f2 * i % MOD;
    ans = (f2 - f1 + MOD) % MOD;
    cout << ans << endl;
    return 0;
}
