#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 10007;
const int N = 100005;
ll n, m, ans, a[N], b[N], s1[N][2], s2[N][2];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        s1[b[i]][i % 2]++;
        s2[b[i]][i % 2] = (s2[b[i]][i % 2] + a[i]) % MOD;
    }
    for (int i = 1; i <= n; i++)
    {
        int y = b[i];
        ans += i * ((s2[y][i % 2] - a[i]) + a[i] * (s1[y][i % 2] - 1) % MOD) % MOD;
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}