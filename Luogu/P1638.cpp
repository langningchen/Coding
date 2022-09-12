#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
const int INF = 0x7FFFFFFF;
int n, m, l, r, ans, ansl, ansr, num, sum[N], a[N];
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	l = 1;
	r = 1;
	num = 0;
	ans = INF;
	while (l <= r && r <= n + 1)
	{
		if (num < m)
		{
			r++;
			sum[a[r - 1]]++;
			if (sum[a[r - 1]] == 1)
				num++;
		}
		else
		{
			if (ans > r - l)
			{
				ans = r - l;
				ansl = l;
				ansr = r - 1;
			}
			sum[a[l]]--;
			if (sum[a[l]] == 0)
				num--;
			l++;
		}
	}
	cout << ansl << " " << ansr << endl;
	return 0;
}