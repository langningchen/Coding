#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll m, n, B, a[N], as[N], b[N], x[N], y[N];
ll query(ll l, ll r, ll k) {
	ll cnt = 0;
	if (b[l] == b[r]) {
		for (int i = l; i <= r; i++) cnt += (a[i] <= k);
		return cnt; 
	}
	for (int i = l; b[i] == b[l]; i++) cnt += (a[i] <= k);
	for (int i = r; b[i] == b[r]; i--) cnt += (a[i] <= k);
	for (int j = b[l] + 1; j <= b[r] - 1; j++)
		cnt += upper_bound(as + x[j], as + y[j] + 1, k) - (as + x[j]);
	return cnt;
}
int main() {
	freopen("greatwall.in", "r", stdin);
	freopen("greatwall.out", "w", stdout);
	cin >> n >> m;
	for (ll i = 1; i <= n; i++) cin >> a[i];
	B = sqrt(n * log2(n));
	for (ll i = 1; i <= n; i++) b[i] = (i - 1) / B + 1;
	for (ll j = 1; j <= b[n] - 1; j++) {
		x[j] = 1 + (j - 1) * B;
		y[j] = j * B;
	} 
	x[b[n]] = 1 + (b[n] - 1) * B;
	y[b[n]] = n;
	for (ll i = 1; i <= n; i++) as[i] = a[i];
	for (ll j = 1; j <= b[n]; j++) sort(as + x[j], as + y[j] + 1);
	for (ll i = 1; i <= m; i++) {
		ll l, r, k;
		cin >> l >> r >> k;
		cout << query(l, r, k) << " ";
	}
	return 0;
} 
