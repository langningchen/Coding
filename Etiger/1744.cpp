#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
int main() {
    freopen("friendship.in", "r", stdin);
    freopen("friendship.out", "w", stdout);
    ll n, c, w[N];
    cin >> n >> c;
    for (ll i = 1; i <= n; i++) cin >> w[i];
    sort(w + 1, w + 1 + n);
    ll ans = 0;
    ll i = 1, j = n;
    while(i <= j) {
        ans++;
        ll r = c - w[j];
        j--;
        if (w[i] <= r)
           i++;
    }
    cout << ans << endl;
    return 0;
}
