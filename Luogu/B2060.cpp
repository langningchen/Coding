#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m, n, ans;
int main()
{
    cin >> m >> n;
    for (int i = m; i <= n; i++)
        if (i % 17 == 0)
            ans += i;
    cout << ans << endl;
    return 0;
}