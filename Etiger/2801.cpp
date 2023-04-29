#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1005;
const int M = 10005;
ll n, k, c[M], s[M], ma, ans;
int main()
{
    freopen("shopping.in", "r", stdin);
    freopen("shopping.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        c[x]++;
        ma = max(ma, x);
    }
    for (int i = 1; i <= ma; i++)
        s[i] = s[i - 1] + c[i];
    if (k > ma)
    {
        cout << n << endl;
        return 0;
    }
    for (int i = 0; i < ma - k; i++)
        ans = max(ans, s[k + i + 1] - s[i]);
    cout << ans << endl;
    return 0;
}
