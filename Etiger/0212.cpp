#include <bits/stdc++.h>
using namespace std;
int n, j;
int main()
{
	freopen("triangle1.in", "r", stdin);
	freopen("triangle1.out", "w", stdout);
	cin >> n;
	for (int i = n; i >= 1; i--)
	{
		for (j = 0; j < i; j++)
			cout << "@";
		cout << endl;
	}
	return 0;
}
