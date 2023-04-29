#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
ll n, p = 1, q = 2;
ld ans;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ans += q * 1.0 / p;
        q = q + p;
        p = q - p;
    }
    cout << fixed << setprecision(4) << ans << endl;
    return 0;
}