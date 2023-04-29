#include <bits/stdc++.h>
typedef long long ll;
ll n, m;
ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}
bool OnlyHave2Or5(ll x)
{
    while (x > 1)
    {
        if (x % 5 == 0)
            x /= 5;
        else if (x % 2 == 0)
            x /= 2;
        else
            return false;
    }
    return true;
}
int GetDivideLastDigit(ll n, ll m)
{
    ll t = gcd(n, m);
    n /= t;
    m /= t;
    if (n / m * m == n)
    {
        ll t = n / m;
        while (t % 10 == 0)
            t /= 10;
        return t % 10;
    }
    else if (OnlyHave2Or5(m))
    {
        long double t = n / (long double)m;
        while (t - (int)t > 1e-9)
            t *= 10;
        return (int)t % 10;
    }
    else
        return -1;
}
int main()
{
    freopen("decimal.in", "r", stdin);
    freopen("decimal.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    printf("%d\n", GetDivideLastDigit(n, m));
    return 0;
}
