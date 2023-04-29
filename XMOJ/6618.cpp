#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MOD = 1000000;
const ll T = 1005;
ll Answer, t, n, s, b, k, Counter[T], Sum[T], f[2][T * T], sd[T * T];
int main()
{
    scanf("%lld%lld%lld%lld", &t, &n, &s, &b);
    for (ll i = 0; i < n; i++)
    {
        ll Temp;
        scanf("%lld", &Temp);
        Counter[Temp]++;
    }
    for (ll i = 1; i <= t; i++)
        Sum[i] = Sum[i - 1] + Counter[i];
    f[0][0] = 1;
    for (ll i = 0; i <= n; i++)
        sd[i] = 1;
    for (ll i = 1; i <= t; i++)
    {
        for (ll j = 0; j <= Sum[i]; j++)
            f[i % 2][j] = ((sd[j] - sd[j - min(Counter[i], j) - 1]) % MOD + MOD) % MOD;
        sd[0] = f[i % 2][0];
        for (ll j = 1; j <= n; j++)
            sd[j] = (sd[j - 1] + f[i % 2][j]) % MOD;
    }
    for (ll i = s; i <= b; i++)
        Answer = (Answer + f[t % 2][i]) % MOD;
    printf("%lld\t", Answer);
    return 0;
}
