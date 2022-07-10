#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
const int N = 3005;
bool s[N];
int n, f[N][N];
int main()
{
	freopen("sychronization.in", "r", stdin);
	freopen("sychronization.out", "w", stdout);
	int temp1, temp2;
	cin >> n >> temp1;
	for (int i = 1; i < n; i++)
	{
		cin >> temp2;
		if (temp2 < temp1)
			s[i + 1] = 0;
		else
			s[i + 1] = 1;
		temp1 = temp2;
	}
	f[1][1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (s[i] == 0)
		{
			for (int j = 2; j <= i; j++)
			{
				f[i][j] = (f[i][j - 1] + f[i - 1][j - 1]) % MOD;
			}
		}
		else
		{
			for (int j = i; j >= 1; j--)
			{
				f[i][j] = (f[i][j + 1] + f[i - 1][j]) % MOD;
			}
		}
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = (ans + f[n][i]) % MOD;
	}
	cout << ans << endl;
	return 0;
}
