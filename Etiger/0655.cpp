#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
int main() {
    freopen("car2.in","r",stdin);
    freopen("car2.out","w",stdout);
    int n, m, a[N], b[N];
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) cin >> a[i];
    for (ll i = 1; i <= m; i++) cin >> b[i];
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + m);
    ll cnt = 0;
    ll i = 1, j = 1;
    while (i <= n && j <= m) {
        if (a[i] <= b[j]) {
            i++;
            j++;
            cnt++;
        }else j++;
    }
    cout << cnt << endl;
    return 0;
}
