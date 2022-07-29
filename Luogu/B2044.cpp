#include <bits/stdc++.h>
using namespace std;
int a, b, c, Counter;
int main()
{
	cin >> a >> b >> c;
	if (a < 60)
		Counter++;
	if (b < 60)
		Counter++;
	if (c < 60)
		Counter++;
	if (Counter == 1)
		cout << 1 << endl;
	else
		cout << 0 << endl;
	return 0;
}
