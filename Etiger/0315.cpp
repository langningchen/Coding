#include <bits/stdc++.h>
using namespace std;
int n, j;
int main()
{
	freopen("tri.in", "r", stdin);
	freopen("tri.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (j = 0; j < n - i; j++)
			cout << " ";
		for (j = 1; j < i * 2; j++)
			cout << "*";
		cout << endl;
	}
	return 0;
}
