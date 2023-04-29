#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 800005;
struct BRIDGE
{
    ll x, y;
} People[N];
ll T, n, m, k, ans, c[N], MaxY;
ll LowBit(ll x)
{
    return x & (-x);
}
void Add(ll Index, ll Value)
{
    while (Index <= MaxY)
    {
        c[Index] += Value;
        Index += LowBit(Index);
    }
}
ll Sum(ll Index)
{
    ll ReturnValue = 0;
    while (Index > 0)
    {
        ReturnValue += c[Index];
        Index -= LowBit(Index);
    }
    return ReturnValue;
}
int main()
{
    scanf("%lld", &T);
    for (ll t = 0; t < T; t++)
    {
        memset(c, 0, sizeof(c));
        MaxY = 0;
        ans = 0;
        scanf("%lld%lld%lld", &n, &m, &k);
        for (ll i = 1; i <= k; i++)
        {
            scanf("%lld%lld", &People[i].x, &People[i].y);
            People[i].x++;
            People[i].y++;
            MaxY = max(MaxY, People[i].y);
        }
        sort(People + 1, People + k + 1,
             [](BRIDGE a, BRIDGE b)
             {
                 if (a.x == b.x)
                     return a.y > b.y;
                 return a.x < b.x;
             });
        ll SameXCount = 0;
        for (ll i = 1; i <= k; i++)
        {
            ans += Sum(MaxY) - Sum(People[i].y);
            if (People[i].x == People[i + 1].x)
            {
                SameXCount++;
                ans -= SameXCount;
            }
            else
                SameXCount = 0;
            // cout << i << "  " << People[i].x << " " << People[i].y << "  " << Sum(MaxY) << " " << Sum(People[i].y) << endl;
            Add(People[i].y, 1);
        }
        printf("Test case %lld: %lld\n", t + 1, ans);
    }
    return 0;
}
