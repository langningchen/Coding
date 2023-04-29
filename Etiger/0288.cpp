#include <bits/stdc++.h>
using namespace std;
int a, b;
bool isPrime(int x)
{
	if (x <= 1)
		return 0;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0)
			return 0;
	return 1;
}
int main()
{
	freopen("pair.in", "r", stdin);
	freopen("pair.out", "w", stdout);
	cin >> a >> b;
	if (abs(a - b) == 2 && isPrime(a) && isPrime(b))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	return 0;
}
