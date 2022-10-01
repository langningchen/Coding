#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
ll n, c, a[N], sum;
int main()
{
	cin >> n >> c;
	for (ll i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	sort(a, a + n);
	ll l = 0, r = 0;
	for (ll i = 0; i < n; i++)
	{
		while (l < n && a[l] < a[i] - c)
			l++;
		while (r < n && a[r] <= a[i] - c)
			r++;
		if (a[i] - a[l] == c)
			sum += r - l;
	}
	cout << sum << endl;
	return 0;
}
