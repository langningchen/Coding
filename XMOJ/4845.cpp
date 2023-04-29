#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 5050;
const ll M = 505;
ll n, k, up, ans, tree[M][N * 2], h[N];
ll LowBit(ll x)
{
    return x & -x;
}
ll query(ll x, ll y)
{
    ll ret = 0;
    while (x)
    {
        for (ll i = y; i; i -= LowBit(i))
            ret = max(ret, tree[x][i]);
        x -= LowBit(x);
    }
    return ret;
}
void modify(ll x, ll y, ll val)
{
    while (x <= k)
    {
        for (ll i = y; i <= up; i += LowBit(i))
            tree[x][i] = max(tree[x][i], val);
        x += LowBit(x);
    }
}
int main()
{
    scanf("%d%d", &n, &k);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%d", &h[i]);
        up = max(h[i], up);
    }
    k++;
    up += k;
    for (ll i = 1; i <= n; i++)
        for (ll j = k; j > 0; j--)
        {
            ll temp = query(j, j + h[i]);
            ans = max(ans, temp + 1);
            modify(j, j + h[i], temp + 1);
        }
    printf("%d\n", ans);
    return 0;
}
