#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
bool n3, n7, n2, n1;
int main()
{
	cin >> n;
	while (1)
	{
		if ((n % 10) == 3)
			n3 = 1;
		if ((n % 10) == 7)
			n7 = 1;
		if ((n % 10) == 2)
			n2 = 1;
		if ((n % 10) == 1)
			n1 = 1;
		n /= 10;
		if (n < 1)
			break;
	}
	if (n3 && n7 && n2 && n1)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	return 0;
}
