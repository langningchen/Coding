#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll k, w, Sum = 0;
ll C(ll n, ll m)
{
    ll Answer = 1;
    for (ll i = 1; i <= m; i++)
        Answer *= (n - i);
    for (ll i = 2; i <= m; i++)
        Answer = Answer / i;
    return Answer;
}
int main()
{
    freopen("digital.in", "r", stdin);
    freopen("digital.out", "w", stdout);
    scanf("%lld%lld", &k, &w);
    for (ll i = 2; i < w / k + 1; i++)
        Sum += C(1 << k, i);
    if (w % k != 0)
        Sum += (C(1 << k, w / k + 1) -
                C((1 << k) - w % k, w / k + 1));
    printf("%lld\n", Sum);
    return 0;
}
