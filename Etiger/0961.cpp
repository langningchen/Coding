#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, m, B, a[N], b[N], c[N], bm[N];
void add(ll l, ll r, ll k)
{
	ll tag;
	if (b[l] == b[r])
	{
		tag = c[b[l]];
		for (ll i = l; i <= r; i++)
		{
			a[i] += k;
			bm[b[i]] = max(a[i] + tag, bm[b[i]]);
		}
		return;
	}
	tag = c[b[l]];
	for (ll i = l; b[i] == b[l]; i++)
	{
		a[i] += k;
		bm[b[i]] = max(a[i] + tag, bm[b[i]]);
	}
	tag = c[b[r]];
	for (ll i = r; b[i] == b[r]; i--)
	{
		a[i] += k;
		bm[b[i]] = max(a[i] + tag, bm[b[i]]);
	}
	for (ll iB = b[l] + 1; iB <= b[r] - 1; iB++)
	{
		c[iB] += k;
		bm[iB] += k;
	}
}
ll rmp(ll l, ll r)
{
	ll tag;
	ll ans = 0;
	if (b[l] == b[r])
	{
		tag = c[b[l]];
		ans = *max_element(a + l, a + r + 1) + tag;
		return ans;
	}
	tag = c[b[l]];
	for (ll i = l; b[i] == b[l]; i++)
		ans = max(ans, a[i] + tag);
	tag = c[b[r]];
	for (ll i = r; b[i] == b[r]; i--)
		ans = max(ans, a[i] + tag);
	for (ll j = b[l] + 1; j <= b[r] - 1; j++)
		ans = max(ans, bm[j]);
	return ans;
}
int main()
{
	freopen("brain12.in", "r", stdin);
	freopen("brain12.out", "w", stdout);
	cin >> n >> m;
	B = sqrt(n) + 1;
	for (ll i = 1; i <= n; i++)
		b[i] = (i - 1) / B + 1;
	for (ll i = 1; i <= n; i++)
	{
		cin >> a[i];
		bm[b[i]] = max(a[i], bm[b[i]]);
	}
	for (ll i = 1; i <= m; i++)
	{
		ll t, l, r, k;
		cin >> t >> l >> r >> k;
		if (t == 1)
			add(l, r, k);
		else
			cout << rmp(l, r) << endl;
	}
	return 0;
}
