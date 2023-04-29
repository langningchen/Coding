#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll n, m;
struct CITY
{
    ll p, y, id;
} City[N];
int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for (ll i = 0; i < m; i++)
    {
        scanf("%lld%lld", &City[i].p, &City[i].y);
        City[i].id = i;
    }
    sort(City, City + m,
         [](CITY a, CITY b)
         {
             if (a.p == b.p)
                 return a.y < b.y;
             return a.p < b.p;
         });
    ll LastProvince = -1, CityCount = 0;
    for (ll i = 0; i < m; i++)
    {
        if (City[i].p != LastProvince)
        {
            LastProvince = City[i].p;
            CityCount = 1;
        }
        else
            CityCount++;
        City[i].y = CityCount;
    }
    sort(City, City + m,
         [](CITY a, CITY b)
         {
             return a.id < b.id;
         });
    for (ll i = 0; i < m; i++)
        printf("%06lld%06lld\n", City[i].p, City[i].y);
    return 0;
}
