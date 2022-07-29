#include <bits/stdc++.h>
using namespace std;
int x, y, u, v;
int main()
{
	freopen("eagle.in", "r", stdin);
	freopen("eagle.out", "w", stdout);
	cin >> x >> y >> u >> v;
	int d = abs(x - y) % 100;
	d = min(d, 100 - d);
	if (d == 0)
		cout << "0.00" << endl;
	else if (u <= v)
		cout << "never" << endl;
	else
		cout << fixed << setprecision(2) << d * 1.0 / (u - v) << endl;
	return 0;
}
