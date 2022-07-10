#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b, n;
void solveEq()
{
	if (n % a)
		cout << -1 << " ";
	else
		cout << n / a << " ";
}
void solveBF()
{
	ll xbound = n / a;
	for (ll x = xbound; x >= 0; x--)
	{
		ll remain = n - a * x;
		if (remain % b)
			continue;
		ll y = remain / b;
		cout << x + y << " ";
		return;
	}
	cout << -1 << " ";
}
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
void solveMath()
{
	ll x, y;
	ll g = exgcd(a, b, x, y);
	if (n % g)
	{
		cout << "-1 ";
		return;
	}
	a /= g;
	b /= g;
	n /= g;
	x *= n;
	y *= n;
	if (y < 0)
	{
		y += (-y) / a * a;
	}
	if (y < 0)
	{
		y += a;
	}
	y -= y / a * a;
	x = (n - b * y) / a;
	if (x < 0)
	{
		cout << "-1 ";
		return;
	}
	cout << x + y << " ";
	return;
}
int main()
{
	freopen("steps.in", "r", stdin);
	freopen("steps.out", "w", stdout);
	ll t;
	cin >> t;
	for (ll i = 0; i < t; i++)
	{
		cin >> n >> a >> b;
		if (a < b)
			swap(a, b);
		if (a == b)
			solveEq();
		else if (n <= 10000)
			solveBF();
		else
			solveMath();
	}
	return 0;
}
