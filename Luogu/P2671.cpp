#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull MOD = 10007;
const ull N = 100005;
ull n, m, ans, a[N], b[N], s1[N][2], s2[N][2];
int main()
{
    cin >> n >> m;
    for (ull i = 1; i <= n; i++)
        cin >> a[i];
    for (ull i = 1; i <= n; i++)
    {
        cin >> b[i];
        s1[b[i]][i % 2]++;
        s2[b[i]][i % 2] = (s2[b[i]][i % 2] + a[i]) % MOD;
    }
    for (ull i = 1; i <= n; i++)
    {
        ans += i * ((s2[b[i]][i % 2] - a[i]) + a[i] * (s1[b[i]][i % 2] - 1)) % MOD;
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}