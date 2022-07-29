#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int INF = 0x7FFFFFFF;
int n, x, y;
int main()
{
	freopen("destiny.in", "r", stdin);
	freopen("destiny.out", "w", stdout);
	cin >> n;
	int bst = INF;
	for (int i = 1; i < N; i++)
	{
		for (int j = i + 1; j <= N; j++)
		{
			int d = abs(n - i * j);
			if (d < bst)
			{
				x = i;
				y = j;
				bst = d;
			}
		}
	}
	cout << x << "*" << y << "=" << x * y << endl;
	return 0;
}
