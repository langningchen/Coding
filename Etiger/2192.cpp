#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
int n, x[N];
int main() {
	freopen("and.in", "r", stdin);
	freopen("and.out", "w", stdout);
	cin >> n;
	for (ll i = 1; i <= n; i++) {
		cin >> x[i];
	}
	vector<ll> ID[2];
	ll now = 0;
	for (int i = 1; i <= n; i++) ID[0].push_back(i);
	ll ans = 0;
	for (ll p = 30; p >= 0; p--) {
		ll nxt = (now ^ 1);
		ID[nxt].clear();
		for (ll i = 0; i < ID[now].size(); i++) {
			ll id = ID[now][i];
			if ((1LL << p) & x[id]) {
				ID[nxt].push_back(id);
			}
		}
		if (ID[nxt].size() < 2) {
			continue;
		}
		ans ^= (1LL << p);
		now = nxt;
	}
	cout << ans << endl;
	return 0;
}
