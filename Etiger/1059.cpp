#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFFFFFF;
ll m, n, B, a[N], as[N], b[N], x[N], y[N];
ll quert(ll l, ll r, ll k) {
	ll cnt = 0;
	ll Max = -INF;
	if (b[l] == b[r]) {
		for (int i = l; i <= r; i++) if (a[i] <= k && a[i] > Max) cnt = i;
		return cnt;
	}
	for (int i = l; b[i] == b[l]; i++) if (a[i] <= k && a[i] > Max) cnt = i;
	for (int i = r; b[i] == b[r]; i--) if (a[i] <= k && a[i] > Max) cnt = i;
	for (int j = b[l] + 1; j <= b[r] - 1; j++) {
		ll *tmp = (upper_bound(as + x[j], as + y[j] + 1, k) - 1);
		if (*tmp > Max) cnt = tmp - 
	}
	return cnt;
}
int main() {
//	freopen("marathon.in", "r", stdin);
//	freopen("marathon.out", "w", stdout);
	cin >> n >> m;
	for (ll i = 1; i <= n; i++) {
		int a1, b1, c1;
		char c2;
		cin >> a1 >> c2 >> b1 >> c2 >> c1 >> c2;
		a[i] = 60 * 60 * a1 + 60 * b1 + c1;
		cout << a[i] << endl;
	}
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
		cout << quert(l, r, k) << " ";
	}
	return 0;
} 
