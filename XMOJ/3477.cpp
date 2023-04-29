#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 3005;
ll n, Answer;
int main()
{
#ifndef __LOCAL__
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
#endif
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        ll x;
        scanf("%lld", &x);
        Answer += x - 1;
    }
    printf("%lld", Answer);
    return 0;
}
