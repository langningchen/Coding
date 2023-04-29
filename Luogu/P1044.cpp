#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 20;
ll n, f[N];
int main()
{
    cin >> n;
    f[1] = 1;
    for (ll i = 2; i <= n; i++)
        f[i] += f[i - 1] * (4 * i - 2) / (i + 1);
    cout << f[n] << endl;
    return 0;
}
