#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, x[N], res[N][N];
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	for (int i = 1; i <= n; i++)
	{
		res[i][0] = 1;
		res[i][1] = x[i];
		for (int j = 1; j < i; j++)
			if (x[j] < x[i])
			{
				int temp1 = 0, temp2 = 0;
				for (int k = 1; k <= res[j][0]; k++)
					temp1 += res[j][k];
				temp1 += x[i];
				for (int k = 1; k <= res[i][0]; k++)
					temp2 += res[i][k];
				if (temp2 < temp1)
				{
					for (int k = 0; k <= res[j][0]; k++)
						res[i][k] = res[j][k];
					res[i][0]++;
					res[i][res[i][0]] = x[i];
				}
			}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int temp = 0;
		for (int j = 1; j <= res[i][0]; j++)
			temp += res[i][j];
		ans = max(ans, temp);
	}
	cout << ans << endl;
	return 0;
}
