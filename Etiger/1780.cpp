#include <bits/stdc++.h>
using namespace std;
int a, b, ans;
bool isLeap(int y)
{
	if (y % 400 == 0 || y % 4 == 0 && y % 100 != 0)
		return 1;
	else
		return 0;
}
int main()
{
	freopen("leapyear.in", "r", stdin);
	freopen("leapyear.out", "w", stdout);
	cin >> a >> b;
	for (int y = a; y <= b; y++)
	{
		if (isLeap(y))
			ans++;
	}
	cout << ans << endl;
	return 0;
}
