#include <bits/stdc++.h>
using namespace std;
int L, x, y;
double a, b;
int main()
{
	freopen("ratio.in", "r", stdin);
	freopen("ratio.out", "w", stdout);
	cin >> a >> b >> L;
	double ratio = a / b;
	double bst = L;
	for (int i = 1; i <= L; i++)
	{
		for (int j = 1; j <= L; j++)
		{
			double d = i * 1.0 / j - ratio;
			if (d >= 0 && d < bst)
			{
				bst = d;
				x = i;
				y = j;
			}
		}
	}
	cout << x << " " << y << endl;
	return 0;
}
