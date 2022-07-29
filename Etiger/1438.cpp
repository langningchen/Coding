#include <bits/stdc++.h>
using namespace std;
const int N = 25;
int n, yh[N][N];
int main()
{
	freopen("yh.in", "r", stdin);
	freopen("yh.out", "w", stdout);
	cin >> n;
	yh[1][1] = 1;
	for (int i = 2; i <= n; i++)
		for (int j = 1; j <= i; j++)
			yh[i][j] = yh[i - 1][j - 1] + yh[i - 1][j];
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			cout << yh[i][j];
			if (j != i)
				cout << " ";
		}
		cout << endl;
	}
	return 0;
}
