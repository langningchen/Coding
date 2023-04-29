#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int MOD = 1000007;
long long n, f[N];
int main()
{
    freopen("monster.in", "r", stdin);
    freopen("monster.out", "w", stdout);
    cin >> n;
    f[0] = 1;
    f[1] = 2;
    for (int i = 2; i <= n; i++)
        f[i] = (f[i - 1] + f[i - 2]) % MOD;
    cout << f[n] << endl;
    return 0;
}
