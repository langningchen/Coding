#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 10005;
struct DATA
{
    ll x, y, h;
} Data[N];
ll n;
int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &Data[i].x, &Data[i].y, &Data[i].h);
    for (ll x = 0; x <= 100; x++)
        for (ll y = 0; y <= 100; y++)
        {
            ll Index = 1;
            while (Data[Index].h == 0)
                Index++;
            ll H = abs(x - Data[Index].x) + abs(y - Data[Index].y) + Data[Index].h;
            bool flag = true;
            for (ll i = 1; i <= n; i++)
                if (max(H - abs(x - Data[i].x) - abs(y - Data[i].y), 0LL) != Data[i].h)
                {
                    flag = false;
                    break;
                }
            if (flag)
            {
                printf("%lld %lld %lld\n", x, y, H);
                return 0;
            }
        }
    return 0;
}
