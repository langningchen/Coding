#include <bits/stdc++.h>
using namespace std;
int n, j;
int main()
{
	freopen("triangle2.in", "r", stdin);
	freopen("triangle2.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (j = 0; j < n - i; j++)
			cout << " ";
		for (j = 0; j < i; j++)
			cout << "#";
		cout << endl;
	}
	return 0;
}
