#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 50005;
const ll M = 2000005;
ll n, q[M], s[M], top;
ll f[N];
struct NODE
{
    ll a, b;
} p[N];
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld%lld", &p[i].a, &p[i].b);
    sort(p + 1, p + n + 1,
         [](NODE x, NODE y)
         {
             return x.a < y.a;
         });
    for (ll i = 1; i <= n; i++)
    {
        while (top && p[s[top]].b <= p[i].b)
            top--;
        top++;
        s[top] = i;
    }
    ll l = 0, r = 0;
    for (ll i = 1; i <= top; i++)
    {
        while (l < r && f[s[q[l + 1]]] - f[s[q[l]]] <= (p[s[q[l] + 1]].b - p[s[q[l + 1] + 1]].b) * (p[s[i]].a))
            l++;
        f[s[i]] = f[s[q[l]]] + p[s[i]].a * p[s[q[l] + 1]].b;
        while (l < r &&
               (f[s[q[r]]] - f[s[q[r - 1]]]) * (p[s[i + 1]].b - p[s[q[r] + 1]].b) <=
                   (f[s[i]] - f[s[q[r]]]) * (p[s[q[r] + 1]].b - p[s[q[r - 1] + 1]].b))
            r--;
        r++;
        q[r] = i;
    }
    printf("%lld\n", f[s[top]]);
    return 0;
}
