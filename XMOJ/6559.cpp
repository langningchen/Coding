#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
const ll M = 4;
ll tot, s, c[M], d[M], f[N], Answer;
void dfs(ll x, ll y, ll sum)
{
    if (sum < 0)
        return;
    if (x >= 4)
    {
        if (y & 1)
            Answer -= f[sum];
        else
            Answer += f[sum];
        return;
    }
    dfs(x + 1, y, sum);
    dfs(x + 1, y + 1, sum - c[x] * (d[x] + 1));
}
int main()
{
    scanf("%d%d%d%d%d", &c[0], &c[1], &c[2], &c[3], &tot);
    f[0] = 1;
    for (ll i = 0; i < M; i++)
        for (ll j = c[i]; j < N; j++)
            f[j] += f[j - c[i]];
    while (tot-- > 0)
    {
        Answer = 0;
        scanf("%d%d%d%d%d", &d[0], &d[1], &d[2], &d[3], &s);
        dfs(0, 0, s);
        printf("%lld\n", Answer);
    }
    return 0;
}
