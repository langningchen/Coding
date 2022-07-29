#include <bits/stdc++.h>
using namespace std;
int i;
int main()
{
	cin >> i;
	for (int m = 0; m < i; m++)
	{
		int a1 = 0, a2 = 0;
		cin >> a1 >> a2;
		if (abs(a1 - a2) == 1)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}
