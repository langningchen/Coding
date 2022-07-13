#include <bits/stdc++.h>
using namespace std;
const int N = 400005;
int n, x[N], s[N], MIN[N], q[N], f[N];
int main()
{
	freopen("woof.in", "r", stdin);
	freopen("woof.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	for (int i = n + 1; i <= n * 2; i++)
		x[i] = x[i - n];
	for (int i = 1; i <= n * 2; i++)
		s[i] = s[i - 1] + x[i];
	int k = n;
	int l = 0, r = 0;
	for (int i = 0; i <= n * 2; i++)
	{
		while (l < r && i - q[l] >= k)
			l++;
		while (l < r && s[i] < s[q[r - 1]])
			r--;
		q[r++] = i;
		MIN[i] = s[q[l]];
	}
	for (int i = 1; i <= n * 2; i++)
		f[i] = s[i] - MIN[i - 1];
	int ans = *max_element(f + 1, f + n * 2 + 1);
	cout << ans << endl;
	return 0;
}
