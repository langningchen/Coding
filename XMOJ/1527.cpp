#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1000005;
ll n, m, a[N], b[N], f[N];
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= m; i++)
        scanf("%lld%lld", &a[i], &b[i]);
    for (ll i = 1; i <= m; i++)
        for (ll j = n; j >= 0; j--)
            if (j >= a[i])
                f[j] = max(f[j], f[j - a[i]] + b[i] * a[i]);
    printf("%lld\n", f[n]);
    return 0;
}
