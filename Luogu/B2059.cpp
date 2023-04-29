#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m, n, ans;
int main()
{
    cin >> m >> n;
    for (int i = (m % 2 == 0 ? m + 1 : m); i <= n; i += 2)
        ans += i;
    cout << ans << endl;
    return 0;
}