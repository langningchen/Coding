#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b, ans;
char c;
int main()
{
	freopen("calculation.in", "r", stdin);
	freopen("calculation.out", "w", stdout);
	cin >> a >> c >> b;
	if (c == '+')
	{
		ans = a + b;
		cout << ans << endl;
	}
	else if (c == '-')
	{
		ans = a - b;
		cout << ans << endl;
	}
	else if (c == '*')
	{
		ans = a * b;
		cout << ans << endl;
	}
	return 0;
}