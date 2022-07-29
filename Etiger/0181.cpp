#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct bign
{
	int d[100000];
	ll len;
	bign()
	{
		memset(d, 0, sizeof(d));
		len = 0;
	}
};
ll n;
bign sum[2];

bign change(char str[])
{
	bign a;
	a.len = strlen(str);
	for (ll i = 0; i < a.len; i++)
		a.d[i] = str[a.len - i - 1] - '0';
	return a;
}

bign change(const char str[])
{
	bign a;
	a.len = strlen(str);
	for (ll i = 0; i < a.len; i++)
		a.d[i] = str[a.len - i - 1] - '0';
	return a;
}

bign change(int x)
{
	int i = 0;
	bign a;
	while (x > 0)
	{
		a.d[i++] = x % 10;
		x /= 10;
	}
	a.len = i;
	return a;
}

bign change(ll x)
{
	ll i = 0;
	bign a;
	while (x > 0)
	{
		a.d[i++] = x % 10;
		x /= 10;
	}
	a.len = i;
	return a;
}

void prll(bign a)
{
	for (ll i = a.len - 1; i >= 0; i--)
		cout << a.d[i];
}

bign add(bign a, bign b)
{
	bign c;
	ll carry = 0;
	for (ll i = 0; i < a.len || i < b.len; i++)
	{
		ll temp = a.d[i] + b.d[i] + carry;
		c.d[c.len++] = temp % 10;
		carry = temp / 10;
	}
	if (carry != 0)
		c.d[c.len++] = carry;
	return c;
}

bign sub(bign a, bign b)
{
	bign c;
	for (ll i = 0; i < a.len || i < b.len; i++)
	{
		if (a.d[i] < b.d[i])
		{
			a.d[i + 1]--;
			a.d[i] += 10;
		}
		c.d[c.len++] = a.d[i] - b.d[i];
	}
	while (c.len - 1 >= 1 && c.d[c.len - 1] == 0)
		c.len--;
	return c;
}

bign multi(bign a, ll b)
{
	bign c;
	ll carry = 0;
	for (ll i = 0; i < a.len; i++)
	{
		ll temp = a.d[i] * b + carry;
		c.d[c.len++] = temp % 10;
		carry = temp / 10;
	}
	while (carry != 0)
	{
		c.d[c.len++] = carry % 10;
		carry /= 10;
	}
	return c;
}

bign divide(bign a, ll b, ll &r)
{
	bign c;
	c.len = a.len;
	for (ll i = a.len - 1; i >= 0; i--)
	{
		r = r * 10 + a.d[i];
		if (r < b)
			c.d[i] = 0;
		else
		{
			c.d[i] = r / b;
			r = r % b;
		}
	}
	while (c.len - 1 >= 1 && c.d[c.len - 1] == 0)
	{
		c.len--;
	}
	return c;
}

int main()
{
	cin >> n;
	sum[0] = sum[1] = change(1);
	for (ll i = 1; i <= n; i++)
		sum[(i % 2 + 1) % 2] = multi(sum[i % 2], i);
	prll(sum[(n % 2 + 1) % 2]);
	cout << endl;
	return 0;
}
