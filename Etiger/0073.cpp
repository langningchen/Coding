#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll solve(ll n)
{
	ll res = 0;
	for (ll l = 1, r; l <= n; l = r + 1)
	{
		ll val = n / l;
		r = n / val;
		res += val * (l + r) * (r - l + 1) / 2;
	}
	return res;
}
int main()
{
	int X, Y;
	cin >> X >> Y;
	cout << solve(Y) - solve(X - 1) << endl;
	return 0;
}
