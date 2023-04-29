#include <bits/stdc++.h>
using namespace std;
int cnt;
char ch;
int main()
{
	freopen("title.in", "r", stdin);
	freopen("title.out", "w", stdout);
	while (cin >> ch)
		if (ch != ' ')
			cnt++;
	cout << cnt << endl;
	return 0;
}
