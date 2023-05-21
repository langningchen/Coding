#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 50005;
const ll LOG_N = 20;
ll a[N], f[N][LOG_N];
ll query(ll l, ll r)
{
    if (l > r)
        return 0;
    ll k = 0;
    while ((1 << (k + 1)) <= r - l + 1)
        k++;
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}
int main()
{
    ll n;
    while (scanf("%lld", &n) != EOF)
    {
        vector<ll> YearList;
        map<ll, ll> YearIndex;
        for (ll i = 1; i <= n; i++)
        {
            ll y;
            scanf("%lld%lld", &y, &a[i]);
            f[i][0] = a[i];
            YearIndex[y] = i;
            YearList.push_back(y);
        }

        for (ll j = 1; (1 << j) <= n; j++)
            for (ll i = 1; i + (1 << j) - 1 <= n; i++)
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);

        ll m;
        scanf("%lld", &m);
        while (m--)
        {
            ll x, y;
            scanf("%lld%lld", &y, &x);
            if (YearIndex[x] == 0 && YearIndex[y] == 0)
                printf("maybe\n");
            else if (YearIndex[x] != 0 && YearIndex[y] == 0)
            {
                if (query(lower_bound(YearList.begin(), YearList.end(), y) - YearList.begin() + 1, YearIndex[x] - 1) >= a[YearIndex[x]])
                    printf("false\n");
                else
                    printf("maybe\n");
            }
            else if (YearIndex[x] == 0 && YearIndex[y] != 0)
            {
                if (query(YearIndex[y] + 1, lower_bound(YearList.begin(), YearList.end(), x) - YearList.begin()) >= a[YearIndex[y]])
                    printf("false\n");
                else
                    printf("maybe\n");
            }
            else if (YearIndex[x] != 0 && YearIndex[y] != 0)
            {
                if (query(YearIndex[y] + 1, YearIndex[x] - 1) >= a[YearIndex[x]] || a[YearIndex[x]] > a[YearIndex[y]])
                    printf("false\n");
                else if (YearIndex[x] - YearIndex[y] != (x - y))
                    printf("maybe\n");
                else
                    printf("true\n");
            }
        }
    }
    return 0;
}
