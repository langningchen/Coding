#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 35;
ll n, f[N];
int main()
{
    freopen("photo.in", "r", stdin);
    freopen("photo.out", "w", stdout);
    cin >> n;
    f[0] = 1;
    for (ll i = 1; i <= n; i++)
        f[i] = f[i - 1] * (4 * i - 2) / (i + 1);
    cout << f[n] << endl;
    return 0;
}
