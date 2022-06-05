#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll xp, yp;
	ll g = exgcd(b, a % b, xp, yp);
	x = yp;
	y = xp - a / b * yp;
	return g;
}
ll inverse(ll a, ll MOD) {
	ll x, y;
	ll g = exgcd(a, MOD, x, y);
	if (g == 1) return (x % MOD + MOD) % MOD;
	return 0;
}
int main() {
	freopen("inverse.in", "r", stdin);
	freopen("inverse.out", "w", stdout);
	int t;
	cin >> t;
	for (ll i = 0; i < t; i++) {
		ll a, m;
		cin >> a >> m;
		cout << inverse(a, m) << " ";
	}
	return 0;
}
