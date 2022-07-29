#include <bits/stdc++.h>
using namespace std;
string s, a, b, temp;
int main()
{
	getline(cin, temp);
	s += " ";
	s += temp;
	s += " ";
	getline(cin, temp);
	a += " ";
	a += temp;
	a += " ";
	getline(cin, temp);
	b += " ";
	b += temp;
	b += " ";
	int start = s.find(a);
	if (start < s.size() && start >= 0)
	{
		s.erase(start, start + a.size());
		s.insert(start, b);
	}
	s.erase(0, 1);
	s.erase(s.size() - 1, s.size());
	cout << s << endl;
	return 0;
}
