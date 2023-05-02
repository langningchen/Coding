#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll X = 130;
const ll D = 25;
ll d, n, x[D], y[D], k[D], f[X][X], MaxValue, MaxCount;
bool InSquare(ll i, ll j, ll t)
{
    if (x[t] <= i + d && x[t] >= i - d)
        if (y[t] <= j + d && y[t] >= j - d)
            return true;
    return false;
}
int main()
{
    scanf("%lld%lld", &d, &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &x[i], &y[i], &k[i]);
    for (ll i = 0; i <= 128; i++)
        for (ll j = 0; j <= 128; j++)
        {
            for (ll t = 1; t <= n; t++)
                if (InSquare(i, j, t))
                    f[i][j] += k[t];
            if (f[i][j] > MaxValue)
            {
                MaxCount = 1;
                MaxValue = f[i][j];
            }
            else if (MaxValue == f[i][j])
                MaxCount++;
        }
    printf("%lld %lld\n", MaxCount, MaxValue);
    return 0;
}
