#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll N = 1005;
const ld INF = (numeric_limits<ld>::max)();
ll n, t, a, h[N], Answer;
ld MinDelta = INF;
int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &t, &a);
    for (ll i = 0; i < n; i++)
    {
        scanf("%lld", &h[i]);
        ld Temp = abs(a - (t - h[i] * 0.006));
        if (Temp < MinDelta)
        {
            MinDelta = Temp;
            Answer = i + 1;
        }
    }
    printf("%lld\n", Answer);
    return 0;
}
