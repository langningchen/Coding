#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
ll n, c, a[N], sum;
int main() {
	cin >> n >> c;
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < n; i++) {
		ll l = 0, r = n;
		while (l < r && a[l] >= a[i] - c) l++;
		while (l < r && a[r] < a[i] - c) r--;
		sum += r - l;
	}
	cout << sum << endl;
	return 0;
}
