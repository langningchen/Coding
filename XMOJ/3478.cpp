#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
ll n, a[N], Delta, MiddleValue;
int main()
{
#ifndef __LOCAL__
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
#endif
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        a[i] -= i;
    }
    sort(a + 1, a + n + 1);
    MiddleValue = a[(n + 1) / 2];
    for (ll i = 1; i <= n; i++)
        Delta += abs(a[i] - MiddleValue);
    printf("%lld\n", Delta);
    return 0;
}
