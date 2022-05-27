#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll o[205][3];
ll a[1005];
ll m, n;
int main() {
	cin >> n >> m;
	for (ll i = 1; i <= n; i++) cin >> a[i];
	for (ll i = 1; i <= m; i++) cin >> o[i][0] >> o[i][1] >> o[i][2];
	for (ll i = m; i > 0; i--) {
		if (o[i][0] == 1 && o[i][1] == o[i][2]) a[o[i][1]] /= 2;
		else if (o[i][0] == 1) a[o[i][1]] -= a[o[i][2]];
		else if (o[i][1] == o[i][2]) a[o[i][1]] = sqrt(a[o[i][1]]);
		else a[o[i][1]] /= a[o[i][2]];
	}
	for (ll i = 1; i <= n; i++) cout << a[i] << " ";
	return 0;
}

