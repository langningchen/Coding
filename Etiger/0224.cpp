#include <bits/stdc++.h>
using namespace std;
int n, x, m;
int main()
{
	cin >> n >> x >> m;
	if (n - x <= 0)
		cout << 0 << endl;
	else
		cout << ceil((n - x) * 1.0 / m) << endl;
	return 0;
}
