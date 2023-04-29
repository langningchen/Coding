#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 50005;
const ll MOD = 10007;
ll n, m, L[N], f[N], sum[N], Answer1, Answer2;
ll IsOK(ll mid)
{
    ll Counter = 0, i = 1;
    while (i <= n)
    {
        if (L[i] - L[i - 1] > mid)
            return m + 1;
        ll Tempi = i;
        while (Tempi <= n && L[Tempi] - L[i - 1] <= mid)
            Tempi++;
        i = Tempi;
        Counter++;
        if (Counter - 1 > m)
            return m + 1;
    }
    return Counter - 1;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%d", &L[i]);
        L[i] += L[i - 1];
    }
    ll Left = 1, Right = L[n];
    while (Left <= Right)
    {
        ll Middle = (Left + Right) >> 1;
        if (IsOK(Middle) <= m)
        {
            Answer1 = Middle;
            Right = Middle - 1;
        }
        else
            Left = Middle + 1;
    }
    for (ll i = 1; i <= n; i++)
        if (L[i] <= Answer1)
            f[i] = 1;
    Answer2 = (L[n] <= Answer1 ? 1 : 0);
    for (ll i = 1; i <= m; i++)
    {
        for (ll j = 1; j <= n; j++)
        {
            sum[j] = (f[j] + sum[j - 1]) % MOD;
            f[j] = 0;
        }
        ll l = 1;
        for (ll j = i + 1; j <= n; j++)
        {
            while (l <= j && L[j] - L[l - 1] > Answer1)
                l++;
            f[j] = (sum[j - 1] - sum[l - 2] + MOD) % MOD;
        }
        Answer2 = (Answer2 + f[n]) % MOD;
    }
    cout << Answer1 << " " << Answer2 << endl;
    return 0;
}
