#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool ok(ll x)
{
	do
	{
		if (x % 2 == 1)
			return 0;
		x /= 10;
	} while (x);
	return 1;
}
const ll N = 10009;
ll ans[N];
int main()
{
	ll n, m;
	cin >> n >> m;
	int cnt = 0;
	for (int i = n; i <= m; i++)
		if (ok(i))
		{
			ans[cnt] = i;
			cnt++;
		}
	for (int i = 0; i < cnt - 1; i++)
		cout << ans[i] << "+";
	cout << ans[cnt - 1] << endl;
	return 0;
}
