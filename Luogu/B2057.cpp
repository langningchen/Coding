#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, ans;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ll t;
        cin >> t;
        ans = max(ans, t);
    }
    cout << ans << endl;
    return 0;
}