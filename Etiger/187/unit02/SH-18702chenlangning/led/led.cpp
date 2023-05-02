#include <bits/stdc++.h>
using namespace std;
const int N = 305;
int m, n, s, t, blackcount, blackline;
bool Map[N][N];
int main()
{
	freopen("led.in", "r", stdin);
	freopen("led.out", "w", stdout):
	cin >> m >> n >> s >> t;
	for (int i = 0; i < m; i++)
	{
		bool flag = true;
		for (int j = 0; j < n; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 0)
			{
				blackcount++;
				flag = false;
			}
		}
		if (!flag)
			blackline++;
	}
	if (blackcount <= t || blackline <= s)
	{
		cout << m * n << endl;
		return 0;
	}
	if (s == 0 && t == 0)
	{
	}
	return 0;
}
