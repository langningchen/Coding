#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll n, MaxValue, MinValue = INF;
int main()
{
#ifndef __LOCAL__
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif
    scanf("%lld", &n);
    for (ll i = 0; i < n; i++)
    {
        ll x;
        scanf("%lld", &x);
        MaxValue = max(MaxValue, x);
        MinValue = min(MinValue, x);
    }
    printf("%lld", MaxValue - MinValue);
    return 0;
}
