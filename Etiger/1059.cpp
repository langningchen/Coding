#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll m, n, B, b[N], x[N], y[N];
pair<ll, ll> a[N], as[N];
ll query(ll l, ll r, ll k)
{
	pair<ll, ll> cnt;
	if (b[l] == b[r])
	{
		for (int i = l; i <= r; i++)
			if (a[i] <= make_pair(k, INF))
				cnt = max(cnt, a[i]);
		return cnt.second;
	}
	for (int i = l; b[i] == b[l]; i++)
		if (a[i] <= make_pair(k, INF))
			cnt = max(cnt, a[i]);
	for (int i = r; b[i] == b[r]; i--)
		if (a[i] <= make_pair(k, INF))
			cnt = max(cnt, a[i]);
	for (int j = b[l] + 1; j <= b[r] - 1; j++)
	{
		pair<ll, ll> tmp = *(upper_bound(as + x[j], as + y[j] + 1, make_pair(k, INF)) - 1);
		if (tmp <= make_pair(k, INF))
			cnt = max(cnt, tmp);
	}
	return cnt.second;
}
int main()
{
	freopen("marathon.in", "r", stdin);
	freopen("marathon.out", "w", stdout);
	cin >> n >> m;
	for (ll i = 1; i <= n; i++)
	{
		int a1, b1, c1;
		char c2;
		cin >> a1 >> c2 >> b1 >> c2 >> c1 >> c2;
		a[i].second = i;
		a[i].first = 60 * 60 * a1 + 60 * b1 + c1;
	}
	B = sqrt(n * log2(n));
	for (ll i = 1; i <= n; i++)
		b[i] = (i - 1) / B + 1;
	for (ll j = 1; j <= b[n] - 1; j++)
	{
		x[j] = 1 + (j - 1) * B;
		y[j] = j * B;
	}
	x[b[n]] = 1 + (b[n] - 1) * B;
	y[b[n]] = n;
	for (ll i = 1; i <= n; i++)
		as[i] = a[i];
	for (ll j = 1; j <= b[n]; j++)
		sort(as + x[j], as + y[j] + 1);
	for (ll i = 1; i <= m; i++)
	{
		ll l, r, k;
		cin >> l >> r >> k;
		cout << query(l, r, k) << " ";
	}
	cout << endl;
	return 0;
}
