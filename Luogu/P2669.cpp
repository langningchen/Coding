#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll k, ans, i = 1;
int main()
{
    cin >> k;
    while (1)
    {
        ans += min(i, k) * i;
        k -= i;
        i++;
        if (k <= 0)
            break;
    }
    cout << ans << endl;
    return 0;
}
