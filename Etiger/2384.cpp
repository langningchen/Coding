#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1000005;
ll f[N];
ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	ll xp, yp;
	ll g = exgcd(b, a % b, xp, yp);
	x = yp;
	y = xp - a / b * yp;
	return g;
}
ll inverse(ll a, ll MOD)
{
	ll x, y;
	ll g = exgcd(a, MOD, x, y);
	if (g == 1)
		return (x % MOD + MOD) % MOD;
	return 0;
}
ll C(ll n, ll m, ll p)
{
	f[0] = 1;
	for (ll x = 1; x <= n; x++)
		f[x] = f[x - 1] * x % p;
	ll res = f[n];
	res = res * inverse(f[m], p) % p;
	res = res * inverse(f[n - m], p) % p;
	return res;
}
int main()
{
	freopen("combination.in", "r", stdin);
	freopen("combination.out", "w", stdout);
	int t;
	cin >> t;
	for (ll i = 0; i < t; i++)
	{
		ll n, m, p;
		cin >> n >> m >> p;
		cout << C(n, m, p) << " ";
	}
	cout << endl;
	return 0;
}
