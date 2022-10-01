#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 15;
const ll INF = 0x0FFFFFFF;
int d[N][N], n, p[N];
void Floyd()
{
	for (int k = 0; k <= n; k++)
	{
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= n; j++)
			{
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
}
void Input()
{
	cin >> n;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			cin >> d[i][j];
		}
	}
}
ll dist()
{
	ll ans = d[p[n]][0];
	for (int i = 1; i <= n; i++)
	{
		ans += d[p[i - 1]][p[i]];
	}
	return ans;
}
int main()
{
	Input();
	Floyd();
	ll ans = INF;
	for (int i = 1; i <= n; i++)
		p[i] = i;
	do
	{
		ans = min(ans, dist());
	} while (next_permutation(p + 1, p + 1 + n));
	cout << ans << endl;
	return 0;
}
