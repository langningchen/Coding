#include <bits/stdc++.h>
using namespace std;
int L, u, v;
double ans;
int main()
{
	freopen("bridge.in", "r", stdin);
	freopen("bridge.out", "w", stdout);
	cin >> L >> u >> v;
	ans = 100 - L * 1.0 / (u + v) * 2;
	if (ans > 0)
		cout << fixed << setprecision(2) << ans << endl;
	else
		cout << fixed << setprecision(2) << 0.00 << endl;
	return 0;
}
