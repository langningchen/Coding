#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
int main()
{
	freopen("wuli.in", "r", stdin);
	freopen("wuli.out", "w", stdout);
	cin >> n >> m;
	ll res0 = 0;
	ll res1 = (1LL << 31) - 1;
	for (ll i = 1; i <= n; i++)
	{
		string op;
		int t;
		cin >> op >> t;
		if (op[0] == 'A')
		{
			res0 &= t;
			res1 &= t;
		}
		else if (op[0] == 'O')
		{
			res0 |= t;
			res1 |= t;
		}
		else if (op[0] == 'X')
		{
			res0 ^= t;
			res1 ^= t;
		}
	}
	ll ans = 0;
	for (ll p = 30; p >= 0; p--)
	{
		if ((1LL << p) & res0)
		{
			ans += (1LL << p);
		}
		else if (((1LL << p) & res1) && (1LL << p) <= m)
		{
			ans += (1LL << p);
			m -= (1LL << p);
		}
	}
	cout << ans << endl;
	return 0;
}
