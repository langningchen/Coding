#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll solve(ll n, ll k)
{
	ll res = 0;
	for (ll l = 1, r; l <= n; l = r + 1)
	{
		ll val = k / l;
		if (val)
			r = min(k / val, n);
		else
			r = n;
		res += val * (l + r) * (r - l + 1) / 2;
	}
	return res;
}
int main()
{
	ll n, k;
	cin >> n >> k;
	cout << n * k - solve(n, k) << endl;
	return 0;
}
