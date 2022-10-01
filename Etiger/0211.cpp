#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 0x7FFFFFFF;
ll ans = -INF;
int main()
{
    for (int i = 0; i < 8; i++)
    {
        ll t;
        cin >> t;
        ans = max(ans, t);
    }
    cout << ans << endl;
    return 0;
}