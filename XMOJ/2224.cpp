#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll a, b, n, g[N][N], MaxF[N][N], MinF[N][N];
signed main()
{
    scanf("%lld%lld%lld", &a, &b, &n);
    for (ll i = 0; i < a; i++)
        for (ll j = 0; j < b; j++)
        {
            scanf("%lld", &g[i][j]);
            MaxF[i][j] = MinF[i][j] = g[i][j];
        }
    ll LogN = log2(n);
    for (ll k = 0; k < LogN; k++)
        for (ll i = 0; i + (1 << k) < a; i++)
            for (ll j = 0; j + (1 << k) < b; j++)
            {
                MaxF[i][j] = max(max(MaxF[i][j], MaxF[i + (1 << k)][j + (1 << k)]),
                                 max(MaxF[i + (1 << k)][j], MaxF[i][j + (1 << k)]));
                MinF[i][j] = min(min(MinF[i][j], MinF[i + (1 << k)][j + (1 << k)]),
                                 min(MinF[i + (1 << k)][j], MinF[i][j + (1 << k)]));
            }
    ll Answer = INF;
    for (ll i = 0; i <= a - n; i++)
        for (ll j = 0; j <= b - n; j++)
            Answer = min(Answer,
                         max(max(MaxF[i][j], MaxF[i + n - (1 << LogN)][j + n - (1 << LogN)]),
                             max(MaxF[i + n - (1 << LogN)][j], MaxF[i][j + n - (1 << LogN)])) -
                             min(min(MinF[i][j], MinF[i + n - (1 << LogN)][j + n - (1 << LogN)]),
                                 min(MinF[i + n - (1 << LogN)][j], MinF[i][j + n - (1 << LogN)])));
    printf("%lld\n", Answer);
    return 0;
}
