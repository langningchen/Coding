#include <bits/stdc++.h>
using namespace std;
string s, find1;
int main()
{
	getline(cin, s);
	getline(cin, find1);
	s = " " + s + " ";
	int p = s.find(" " + find1 + " ");
	if (p == -1)
		cout << "sorry";
	else
		cout << p + 1;
	return 0;
}
