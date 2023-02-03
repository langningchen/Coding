#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll N = 200005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll n, a[N], sum[N], ans = INF;
int main()
{
#ifndef __LOCAL__
    freopen("e.in", "r", stdin);
    freopen("e.out", "w", stdout);
#endif
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    ll i = 1, k = 3;
    for (ll j = 2; j < n - 1; j++)
    {
        /*
         * Group          |     P     |      Q      |      R      |      S      |
         * Space Index    0           i             j             k             n
         * Element Index  |1         i|i+1         j|j+1         k|k+1         n|
         * Sum count      |     i     |     j-i     |     k-j     |     n-k     |
         * Group Content  | 0 < ? < i |  i < ? < j  |  j < ? < k  |  k < ? < n  |
         * 1 < i, i + 1 < j, j + 1 < k, k + 1 < n
         */
        while (i < j - 1 && abs((sum[i + 1] - sum[0]) - (sum[j] - sum[i + 1])) <=
                                abs((sum[i] - sum[0]) - (sum[j] - sum[i])))
            i++;
        while (k < n && abs((sum[k + 1] - sum[j]) - (sum[n] - sum[k + 1])) <=
                            abs((sum[k] - sum[j]) - (sum[n] - sum[k])))
            k++;
        ans = min(ans, (max(max(sum[i], sum[j] - sum[i]), max(sum[k] - sum[j], sum[n] - sum[k])) -
                        min(min(sum[i], sum[j] - sum[i]), min(sum[k] - sum[j], sum[n] - sum[k]))));
    }
    printf("%lld\n", ans);
    return 0;
}
