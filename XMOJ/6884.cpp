#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
ll mul(ll a, ll b, ll m)
{
    ll ans = 0;
    while (b)
    {
        if (b & 1)
            ans = (ans + a) % m;
        a = (a + a) % m;
        b >>= 1;
    }
    return ans;
}
ll pow(ll x, ll n, ll m)
{
    ll ans = 1 % m;
    x %= m;
    while (n)
    {
        if (n & 1)
            ans = mul(ans, x, m);
        x = mul(x, x, m);
        n >>= 1;
    }
    return ans;
}
bool MillerRabin(ll n, int k)
{
    if (n <= 2)
        return (n == 2);
    if (n % 2 == 0)
        return false;
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0)
    {
        d >>= 1;
        s++;
    }
    for (int i = 0; i < k; i++)
    {
        ll a = rand() % (n - 2) + 2;
        ll x = pow(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool flag = true;
        for (int j = 1; j < s; j++)
        {
            x = mul(x, x, n);
            if (x == n - 1)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            return false;
    }
    return true;
}
bool IsHappyNumber(ll x)
{
    if (x == 1)
        return false;
    if (MillerRabin(x, 20))
        return false;
    for (ll i = 2; i <= sqrt(x); i++)
        if (x % i == 0 && MillerRabin(i, 20) && MillerRabin(x / i, 20))
            return false;
    return true;
}
int main()
{
    freopen("nprime.in", "r", stdin);
    freopen("nprime.out", "w", stdout);
    scanf("%lld", &n);
    if (IsHappyNumber(n))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
