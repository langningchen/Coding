#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int timer, nGroup, ans, n;
int dfn[N], iGrp[N], t[N];
void move(int u) {
	dfn[u] = ++timer;
	iGrp[u] = nGroup;
	int v = t[u];
	if (!dfn[v]) {
		move(v);
		return;
	}
	if (iGrp[v] == iGrp[u]) {
		ans = min(ans, dfn[u] - dfn[v] + 1);
	}
}
int main() {
	freopen("message.in", "r", stdin);
	freopen("message.out", "w", stdout);
	cin >> n;
	for (int u = 1; u <= n; u++) {
		cin >> t[u];
	}
	ans = n;
	for (int u = 1; u <= n; u++) {
		if (!dfn[u]) {
			++nGroup;
			move(u);
		}
	}
	cout << ans << endl;
	return 0;
}
