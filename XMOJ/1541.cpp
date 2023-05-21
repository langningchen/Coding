#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 10'0005;
const ll INF = 0x3FFF'FFFF'FFFF'FFFF;
ll l, s, t, n, a[N], dp[N];
int main()
{
    scanf("%lld%lld%lld%lld", &l, &s, &t, &n);
    for (ll i = 1; i <= n; ++i)
    {
        ll p;
        scanf("%lld", &p);
        a[p]++;
    }
    dp[0] = 0;
    for (ll i = 1; i <= l + t; i++)
    {
        dp[i] = INF;
        for (ll j = i - t; j <= i - s; j++)
            if (j >= 0)
                dp[i] = min(dp[i], dp[j]);
        dp[i] += a[i];
    }
    ll Answer = INF;
    for (ll i = l; i <= l + t; i++)
        Answer = min(Answer, dp[i]);
    printf("%lld\n", Answer);
    return 0;
}
