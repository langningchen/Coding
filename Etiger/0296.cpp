#include <bits/stdc++.h>
using namespace std;
int n;
int tryit(int i)
{
	return (i == 1 ? 1 : (i == 2 ? 2 : (2 * tryit(i - 1) + tryit(i - 2)))) % 32767;
}
int main()
{
	cin >> n;
	cout << tryit(n) << endl;
	return 0;
}
