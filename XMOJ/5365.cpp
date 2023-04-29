#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 25;
ll n, t, m, ans, a[N], p[N], v[N];
int main()
{
    scanf("%lld%lld%lld", &n, &t, &m);
    for (ll i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    for (ll i = 1; i <= pow(2, n) - 1; i++)
    {
        ll cnt = 0;
        ll Temp = i;
        while (Temp)
        {
            ll j = Temp & (-Temp);
            Temp ^= j;
            j = log2(j * 1.0);
            p[cnt++] = j;
        }
        if (cnt <= ans)
            continue;
        for (ll j = 0; j < m; j++)
            v[j] = t;
        bool flag = false;
        for (ll j = 0, k = 0; j < cnt; j++)
        {
            if (a[p[j]] > t)
            {
                flag = true;
                break;
            }
            if (a[p[j]] <= v[k])
                v[k] -= a[p[j]];
            else
            {
                k++;
                v[k] -= a[p[j]];
            }
            if (k >= m)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            ans = cnt;
    }
    printf("%lld\n", ans);
    return 0;
}
