#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 65540;
ll n, k, ans, a[N], b[N];
int main()
{
    freopen("tiger.in", "r", stdin);
    freopen("tiger.out", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] = ceil(a[i] / 12.0);
    }
    sort(a + 1, a + n + 1);
    ans = a[n] * 12;
    for (int i = 0; i < n; i++)
        b[i] = a[i + 1] - a[i];
    sort(b, b + n);
    for (int i = n - 1; i >= n - (k - 1); i--)
    {
        if (b[i] <= 1)
            break;
        ans -= (b[i] - 1) * 12;
    }
    cout << ans << endl;
    return 0;
}