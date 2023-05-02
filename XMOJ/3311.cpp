#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 305;
const ll M = 105;
ll n, m, q, a[N][N], c[N][N][M];
ll LowBit(ll x)
{
    return x & (-x);
}
void Add(ll x, ll y, ll v)
{
    for (ll i = x; i <= n; i += LowBit(i))
        for (ll j = y; j <= m; j += LowBit(j))
            c[i][j][v]++;
}
ll Sum(ll x, ll y, ll v)
{
    ll Answer = 0;
    for (ll i = x; i > 0; i -= LowBit(i))
        for (ll j = y; j > 0; j -= LowBit(j))
            Answer += c[i][j][v];
    return Answer;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
        {
            scanf("%lld", &a[i][j]);
            Add(i, j, a[i][j]);
        }
    scanf("%lld", &q);
    while (q--)
    {
        ll Operation;
        scanf("%lld", &Operation);
        if (Operation == 1)
        {
            ll x, y, c;
            scanf("%lld%lld%lld", &x, &y, &c);
            Add(x, y, -a[x][y]);
            Add(x, y, c);
            a[x][y] = c;
        }
        else
        {
            ll x1, x2, y1, y2, c;
            scanf("%lld%lld%lld%lld%lld", &x1, &x2, &y1, &y2, &c);
            printf("%lld\n", Sum(x2, y2, c) -
                                 Sum(x1 - 1, y2, c) -
                                 Sum(x2, y1 - 1, c) +
                                 Sum(x1 - 1, y1 - 1, c));
        }
    }
    return 0;
}
