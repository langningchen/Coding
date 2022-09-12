#include <bits/stdc++.h>
using namespace std;
int main()
{
	freopen("power.in", "r", stdin);
	freopen("power.out", "w", stdout);
	long long n = 0;
	cin >> n;
	if (n % 2 == 1)
	{
		cout << -1;
	}
	else
	{
		while (n != 0)
		{
			int t = pow(2, floor(log(n) / log(2)));
			n -= t;
			cout << t << " ";
		}
	}
	cout << endl;
	return 0;
}
