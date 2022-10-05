#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
ll n, m, cnt, p[N], s[N];
int main()
{
#ifndef LOCAL
	freopen("share.in", "r", stdin);
	freopen("share-BF.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> p[i];
		s[i] = (s[i - 1] + p[i]) % m;
	}
#ifdef DEBUG
	for (int i = 0; i < n; i++)
		cout << s[i] << " ";
	cout << endl;
#endif
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < i; j++)
			if ((s[i] - s[j]) % m == 0)
				cnt++;
	cout << cnt << endl;
	return 0;
}
