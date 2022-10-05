#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 300005;
ll n, A, x[N], s[N];
int main()
{
    freopen("income.in", "r", stdin);
    freopen("income.out", "w", stdout);
    cin >> n >> A;
    for (ll i = 1; i <= n; i++)
    {
        cin >> x[i];
        x[i] -= A;
        s[i] = s[i - 1] + x[i];
    }
    sort(s, s + n + 1);
    ll ans = 0;
    ll cnt = 1;
    for (ll i = 1; i <= n; i++)
    {
        if (s[i] != s[i - 1])
        {
            ans += cnt * (cnt - 1) / 2;
            cnt = 0;
        }
        cnt++;
    }
    ans += cnt * (cnt - 1) / 2;
    cout << ans << endl;
    return 0;
}