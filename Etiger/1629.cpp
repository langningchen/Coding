#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 16;
ll n, m;
int main() {
    freopen("qiuhe2.in","r",stdin);
    freopen("qiuhe2.out","w",stdout);
    cin >> n >> m;
    if (n < m) {
        cout << 0 << endl;
        return 0;
    }
    ll ans = 1;
    for (ll i = 1; i <= m - 1; i++) {
        ans *= n - i;
        ans /= i;
    }
    cout << ans << endl;
    return 0;
}
