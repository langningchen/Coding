#include <bits/stdc++.h>
using namespace std;
int n;
bool isHW(string s)
{
	int l = 0;
	int r = s.size() - 1;
	while (l < r)
	{
		if (s[l] != s[r])
			return 0;
		l++;
		r--;
	}
	return 1;
}
int main()
{
	freopen("palindrome.in", "r", stdin);
	freopen("palindrome.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		if (isHW(s))
			cout << "Yes ";
		else
			cout << "No ";
	}
	return 0;
}
