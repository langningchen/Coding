#include <bits/stdc++.h>
using namespace std;
char x;
int main()
{
	freopen("type.in", "r", stdin);
	freopen("type.out", "w", stdout);
	cin >> x;
	if (x >= 'a' && x <= 'z')
		cout << "lowercase" << endl;
	else if (x >= 'A' && x <= 'Z')
		cout << "UPPERCASE" << endl;
	else if (x >= '0' && x <= '9')
		cout << "digit" << endl;
	else
		cout << "other" << endl;
	return 0;
}
