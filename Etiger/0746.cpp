#include <bits/stdc++.h>
using namespace std;
int x, y, h, ans;
int main()
{
	freopen("snail.in", "r", stdin);
	freopen("snail.out", "w", stdout);
	cin >> h >> x >> y;
	if (x >= h)
		ans = 1;
	else if (x > y)
		ans = ceil((h - x) * 1.0 / (x - y) + 1);
	else
		ans = -1;
	cout << ans << endl;
	return 0;
}
