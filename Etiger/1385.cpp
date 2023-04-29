#include <bits/stdc++.h>
using namespace std;
char x, y;
int main()
{
	freopen("comparison.in", "r", stdin);
	freopen("comparison.out", "w", stdout);
	cin >> x >> y;
	if (x < y)
		cout << x << "<" << y << endl;
	else if (x > y)
		cout << x << ">" << y << endl;
	else
		cout << x << "==" << y << endl;
	return 0;
}
