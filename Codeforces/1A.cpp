#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, a, ans;
int main()
{
    cin >> n >> m >> a;
    ans = ceil(n * 1.0 / a) * ceil(m * 1.0 / a);
    cout << ans << endl;
    return 0;
}
