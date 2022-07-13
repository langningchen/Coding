#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
int f[N][N];
ll max(ll a, ll b)
{
	return ((a > b) ? a : b);
}
int main()
{
	string a, b;
	cin >> a >> b;
	ll n = a.size();
	ll m = b.size();
	a = " " + a;
	b = " " + b;
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (a[i] == b[j])
				f[i][j] = f[i - 1][j - 1] + 1;
			ans = max(ans, f[i][j]);
		}
	set<string> s;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (f[i][j] == ans)
				s.insert(a.substr(i - ans + 1, ans));
	cout << *s.begin() << endl;
	cout << ans << endl;
	return 0;
}
