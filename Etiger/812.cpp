#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m;
int main() {
	cin >> n >> m;
	for (ll i = 1; i <= m; i++) {
		ll u ,v;
		cin >> u >> v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	tarjan(rt = 1, 0);
	ll nCnt = 0;
	for (ll u = 1; u <= n; ++u) {
		if (isCut(u)) {
			nCnt++;
			cout << u << endl;
		}
	}
	if (!nCnt) {
		cout << "perfect" << endl;
	}
	return 0;
}
