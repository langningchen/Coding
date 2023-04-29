#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll n, m, w[N], _m[N], num[N], c[35], tot, cnt[35];
ll DFS(ll id)
{
    if (id > tot)
        return 0;
    if (cnt[id])
    {
        cnt[id]--;
        return 1;
    }
    if (DFS(id + 1))
    {
        cnt[id] += c[id + 1] / c[id], cnt[id]--;
        return 1;
    }
    return 0;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (ll i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    for (ll i = 1; i <= m; i++)
        scanf("%d", &_m[i]);
    sort(_m + 1, _m + m + 1);
    for (ll i = 1; i <= m; i++)
    {
        if (_m[i] != _m[i - 1])
        {
            tot++;
            c[tot] = _m[i];
        }
        num[i] = tot;
    }
    for (ll i = 1; i <= n; i++)
        for (ll j = tot; j; j--)
            cnt[j] += w[i] / c[j], w[i] %= c[j];
    for (ll i = 1; i <= m; i++)
        if (!DFS(num[i]))
        {
            printf("%d\n", i - 1);
            return 0;
        }
        else if (i == m)
            printf("%d\n", m);
    return 0;
}
