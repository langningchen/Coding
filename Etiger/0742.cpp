#include <bits/stdc++.h>
using namespace std;
const int N = 50005;
const int MOD = 1000007;
long long n, f[N];
int main()
{
    freopen("monster2.in", "r", stdin);
    freopen("monster2.out", "w", stdout);
    cin >> n;
    f[0] = 1;
    f[1] = 2;
    f[2] = 4;
    for (int i = 3; i <= n; i++)
        f[i] = (f[i - 1] + f[i - 2] + f[i - 3]) % MOD;
    cout << f[n] << endl;
    return 0;
}
