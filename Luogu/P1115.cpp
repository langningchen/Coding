#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7FFFFFFF;
ll n, ans = -INF, f;
int main() {
	cin >> n;
	for (ll i = 0; i < n; i++) {
		ll a;
		cin >> a;
		f = max(f + a, a);
		ans = max(f, ans);
	}
	cout << ans << endl;
	return 0;
}
