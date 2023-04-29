#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
	freopen("paradise.in", "r", stdin);
	freopen("paradise.out", "w", stdout);
	getline(cin, s);
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] > '9' || s[i] < '0')
			cout << s[i];
	}
	cout << endl;
	return 0;
}
