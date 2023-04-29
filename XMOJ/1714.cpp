#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T, n, r;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &r);
        ll ans = 1;
        ll t = n % 10;
        while (t != r && t != 0)
        {
            t = (t + n) % 10;
            ans++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
