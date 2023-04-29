#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll count(ll T, ll x)
{
	ll res = 0;
	do
	{
		if (x % 10 == T)
			res++;
		x /= 10;
	} while (x);
	return res;
}
ll n, ans[15];
int main()
{
	cin >> n;
	for (ll T = 0; T <= 9; T++)
	{
		ll ans = 0;
		for (ll x = 1; x <= n; x++)
			ans += count(T, x);
		cout << T << ":" << ans << endl;
	}
	return 0;
}
