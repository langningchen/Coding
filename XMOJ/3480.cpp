#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1 << 8 + 5;
ll n, a[N], Answer;
ll LowBit(ll x)
{
    return x & (-x);
}
int main()
{
#ifndef __LOCAL__
    freopen("f.in", "r", stdin);
    freopen("f.out", "w", stdout);
#endif
    scanf("%lld", &n);
    n = pow(2, n);
    for (ll i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    sort(a, a + n);
    for (ll k = 1; k < n; k++)
    {
        Answer = 0;
        for (ll x = 1; x <= k; x++)
        {
            cout << x << " " << x - LowBit(x) << endl;
            Answer = max(Answer, a[x] + a[x - LowBit(x)]);
        }
        printf("%lld\n", Answer);
    }
    return 0;
}
