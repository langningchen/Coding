#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500005;
ll n, m;
ll a[N], pxor[N], DEL[N];
int main()
{
	freopen("orxor.in", "r", stdin);
	freopen("orxor.out", "w", stdout);
	scanf("%lld %lld", &n, &m);
	for (ll i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		pxor[i] = pxor[i - 1] ^ a[i];
	}
	ll ans = 0;
	for (ll p = 62; p >= 0; p--)
	{
		ll c0 = 0;
		if ((1LL << p) & pxor[n])
		{
			ans += (1LL << p);
			continue;
		}
		for (ll i = 1; i <= n; i++)
		{
			if (DEL[i])
			{
				continue;
			}
			if ((1LL << p) & pxor[i])
			{
				continue;
			}
			c0++;
		}
		if (c0 < m)
		{
			ans += (1LL << p);
			continue;
		}
		for (ll i = 1; i <= n; i++)
		{
			if (DEL[i])
			{
				continue;
			}
			if ((1LL << p) & pxor[i])
			{
				DEL[i] = 1;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
