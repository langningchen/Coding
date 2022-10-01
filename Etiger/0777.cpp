#include <bits/stdc++.h>
using namespace std;
const int N = 105;
struct people
{
	int xs[N];
};
people p[N];
int main()
{
	int m, n;
	cin >> m >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> p[j].xs[i];
	for (int i = 0; i < m; i++)
		sort(p[i].xs, p[i].xs + n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << p[j].xs[n - i - 1];
			if (j < m - 1)
				cout << ' ';
		}
		if (i < n - 1)
			cout << endl;
	}
	return 0;
}
