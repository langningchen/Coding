#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
string ans;
int main()
{
    freopen("negbin.in", "r", stdin);
    freopen("negbin.out", "w", stdout);
    cin >> n;
    while (n)
        if (n % 2 == 0)
        {
            ans += '0';
            n /= -2;
        }
        else
        {
            ans += '1';
            n = (n - 1) / -2;
        }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
    return 0;
}
