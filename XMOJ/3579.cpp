#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100'005;
ll n, m, a[N], s[N], Answer;
map<ll, ll> cnt;
int main()
{
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        s[i] = (s[i - 1] + a[i]) % m;
        cnt[s[i]]++;
    }
    for (auto i : cnt)
    {
        Answer += i.second * (i.second - 1) / 2;
        Answer += (i.first == 0 ? i.second : 0);
    }
    printf("%lld\n", Answer);
    return 0;
}
