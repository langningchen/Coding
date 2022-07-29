#include <bits/stdc++.h>
using namespace std;
const int N = 5;
int x, y;
char a[N][N];
int main()
{
	freopen("ear.in", "r", stdin);
	freopen("ear.out", "w", stdout);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> a[i][j];
			if (a[i][j] == '*')
			{
				x = i;
				y = j;
			}
		}
	}
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
			if (!(i == x && j == y) && i >= 0 && j >= 0 && i <= 4 && j <= 4)
				a[i][j] = '#';
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << a[i][j];
		cout << endl;
	}
	return 0;
}
