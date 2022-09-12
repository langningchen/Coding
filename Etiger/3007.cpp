#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 35;
ll f[N];
int main()
{
	ll n;
	cin >> n;
	f[0] = 1;
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		f[i] = i * f[i - 1];
		ans += f[i];
	}
	cout << ans << endl;
	return 0;
}
